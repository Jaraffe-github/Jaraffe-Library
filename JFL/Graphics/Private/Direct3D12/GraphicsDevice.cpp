//
//  File: GraphicsDevice.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "../GraphicsAPI.h"
#include "GraphicsDevice.h"
#include "CommandQueue.h"
#include "GPUBuffer.h"
#include "Texture.h"
#include "Types.h"
#include "Log/JFLog.h"
#include "GraphicsDevice.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Direct3D12
{
	JFGraphicsDevice* CreateGraphicsDevice()
	{
		return new GraphicsDevice();
	}
}

using namespace JFL;
using namespace JFL::Private::Direct3D12;

GraphicsDevice::GraphicsDevice()
{
    UINT dxgiFactoryFlags = 0;

    if (GraphicsSettings::VALIDATION)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
            JFLogInfo("Enable D3D12 debug layer.");

            // this is slow for gpu debug.
            ComPtr<ID3D12Debug1> debugController1;
            if (SUCCEEDED(debugController->QueryInterface(IID_PPV_ARGS(&debugController1))))
            {
                debugController1->SetEnableGPUBasedValidation(true);
                JFLogInfo("Enable D3D12 GPU based validation.");
            }
        }
        else
        {
            JFLogWarning("Unable to enable D3D12 debug layer");
        }

        ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
        {
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);

            DXGI_INFO_QUEUE_MESSAGE_ID hide[] =
            {
                80 /* IDXGISwapChain::GetContainingOutput: The swapchain's adapter does not control the output on which the swapchain's window resides. */,
            };
            DXGI_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            dxgiInfoQueue->AddStorageFilterEntries(DXGI_DEBUG_DXGI, &filter);
        }
    }

    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

    // find capable hardware adapter.
    size_t maxSize = 0;
    ComPtr<IDXGIAdapter1> adapter;
    for (uint32_t idx = 0; factory->EnumAdapters1(idx, &adapter) != DXGI_ERROR_NOT_FOUND; ++idx)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            continue;

        if ((desc.DedicatedVideoMemory > maxSize))
        {
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device))))
            {
                JFLogInfo(L"Usable hardware info: {} ({} MB)", desc.Description, desc.DedicatedVideoMemory >> 20);
                maxSize = desc.DedicatedVideoMemory;
            }
        }
    }
    if (device)
    {
        ThrowIfFailed(factory->EnumAdapterByLuid(device->GetAdapterLuid(), IID_PPV_ARGS(&adapter)));

        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        JFLogInfo(L"Selected hardware info: {} ({} MB)", desc.Description, desc.DedicatedVideoMemory >> 20);
    }
    // software adapter.
    else
    {
        JFLogWarning("Failed to find a supportable hardware adapter");

        ComPtr<IDXGIAdapter> warpAdapter;
        ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

        ThrowIfFailed(D3D12CreateDevice(
            warpAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&device)));

        JFLogInfo("Instead used WARP software adapter");
    }

#if defined(DEBUG) || defined(_DEBUG)
    // debug layer filter.
    ID3D12InfoQueue* infoQueue = nullptr;
    if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
    {
        // Suppress whole categories of messages
        //D3D12_MESSAGE_CATEGORY Categories[] = {};

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] =
        {
            D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,
            D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_RT_OUTPUT_MISMATCH,
            D3D12_MESSAGE_ID_COMMAND_LIST_DESCRIPTOR_TABLE_NOT_SET,
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,

            // RESOURCE_BARRIER_DUPLICATE_SUBRESOURCE_TRANSITIONS
            (D3D12_MESSAGE_ID)1008,
        };

        D3D12_INFO_QUEUE_FILTER newFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        newFilter.DenyList.NumSeverities = _countof(Severities);
        newFilter.DenyList.pSeverityList = Severities;
        newFilter.DenyList.NumIDs = _countof(DenyIds);
        newFilter.DenyList.pIDList = DenyIds;

        infoQueue->PushStorageFilter(&newFilter);
        infoQueue->Release();
    }
#endif

    device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &d3d12Options, sizeof(d3d12Options));
    // check UMA(Universal Memory Architecture) usually for mobile
    device->CheckFeatureSupport(D3D12_FEATURE_ARCHITECTURE, &architecture, sizeof(architecture));
}

JFObject<JFCommandQueue> GraphicsDevice::CreateCommandQueue()
{
    ComPtr<ID3D12CommandQueue> queue;
    {
        D3D12_COMMAND_QUEUE_DESC desc{};
        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        ThrowIfFailed(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue)));
    }
    ComPtr<ID3D12Fence> fence;
    {
        ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
    }

    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ThrowIfFailed(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));

    ComPtr<ID3D12GraphicsCommandList> commandList;
    ThrowIfFailed(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
    commandList->Close();

    return new CommandQueue(this, queue.Get(), commandAllocator.Get(), commandList.Get(), fence.Get());
}

JFObject<JFGPUBuffer> GraphicsDevice::CreateGPUBuffer(size_t size, JFGPUBuffer::CPUCacheMode mode)
{
    D3D12_HEAP_PROPERTIES heapProperty{};
    D3D12_RESOURCE_STATES initialResourceState{};
    switch (mode)
    {
    case GPUBuffer::CPUCacheMode::None:
        heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        initialResourceState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case GPUBuffer::CPUCacheMode::WriteCombined:
        heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        initialResourceState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case GPUBuffer::CPUCacheMode::ReadCombined:
        heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
        initialResourceState = D3D12_RESOURCE_STATE_COPY_DEST;
        break;
    }

    D3D12_RESOURCE_DESC bufferDesc;
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Alignment = 0;
    bufferDesc.Width = AlignGPUBufferSize(size);
    bufferDesc.Height = 1;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    ComPtr<ID3D12Resource> buffer;
    ThrowIfFailed(device->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        initialResourceState,
        nullptr,
        IID_PPV_ARGS(buffer.GetAddressOf())));

    return new GPUBuffer(buffer.Get(), mode, initialResourceState);
}

JFObject<JFTexture> GraphicsDevice::CreateTexture(const JFTextureDescriptor& desc)
{
    D3D12_RESOURCE_DESC bufferDesc{};
    bufferDesc.Width = desc.width;
    bufferDesc.Height = desc.height;
    bufferDesc.DepthOrArraySize = desc.depth;
    bufferDesc.MipLevels = desc.mipmapLevelCount;
    bufferDesc.SampleDesc.Count = desc.sampleCount;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Format = PixelFormat(desc.format);

    switch (desc.type)
    {
    case Texture::Type1D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D; break;
    case Texture::Type2D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; break;
    case Texture::Type3D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D; break;
    }

    D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

    // default - allow bind shader.
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    if (desc.usage & Texture::UsageShaderRead)
    {
        initialState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    }
    else
    {
        // for optimize.
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
    }
    if (desc.usage & Texture::UsageRenderTarget)
    {
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        initialState = D3D12_RESOURCE_STATE_RENDER_TARGET;
    }
    if (desc.usage & Texture::UsageDepthStencil)
    {
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        initialState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }

    ComPtr<ID3D12Resource> buffer;
    {
        CD3DX12_HEAP_PROPERTIES heapProperty(D3D12_HEAP_TYPE_DEFAULT);
        ThrowIfFailed(device->CreateCommittedResource(
            &heapProperty,
            D3D12_HEAP_FLAG_NONE,
            &bufferDesc,
            initialState,
            nullptr,
            IID_PPV_ARGS(buffer.GetAddressOf())));
    }

    JFObject<Texture> newTexture = new Texture(buffer.Get(), initialState);

    // Render Target View.
    if (desc.usage & Texture::UsageRenderTarget)
    {
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descriptorHeap;
        ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

        D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
        rtvDesc.Format = bufferDesc.Format;
        switch (bufferDesc.Dimension)
        {
        case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
            rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1D;
            break;
        case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
            rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
            break;
        case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
            rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
            break;
        }

        device->CreateRenderTargetView(buffer.Get(), &rtvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
        newTexture->SetRenderTargetViewHeap(descriptorHeap.Get());
    }

    // Depth Stencil View.
    if (desc.usage & Texture::UsageDepthStencil)
    {
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descriptorHeap;
        ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

        D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
        dsvDesc.Format = bufferDesc.Format;
        switch (desc.type)
        {
        case Texture::Type1D:
            dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
            break;
        case Texture::Type2D:
            dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
            break;
        case Texture::Type3D:
            JFASSERT_DESC_DEBUG(false, "DepthStencil is a format that is not available.");
            break;
        }

        device->CreateDepthStencilView(buffer.Get(), &dsvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
        newTexture->SetDepthStencilViewHeap(descriptorHeap.Get());
    }

    // Shader Resource View
    if (desc.usage & Texture::UsageShaderRead)
    {
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descriptorHeap;
        ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Format = bufferDesc.Format;
        switch (desc.type)
        {
        case Texture::Type1D:
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
            srvDesc.Texture1D.MipLevels = bufferDesc.MipLevels;
            break;
        case Texture::Type2D:
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = bufferDesc.MipLevels;
            break;
        case Texture::Type3D:
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
            srvDesc.Texture3D.MipLevels = bufferDesc.MipLevels;
            break;
        }
        device->CreateShaderResourceView(buffer.Get(), &srvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
        newTexture->SetShaderResourceViewHeap(descriptorHeap.Get());
    }

    return newTexture.Ptr();
}
