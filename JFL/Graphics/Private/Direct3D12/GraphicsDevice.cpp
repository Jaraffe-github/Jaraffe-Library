//
//  File: GraphicsDevice.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "GraphicsDevice.h"
#include "CommandQueue.h"
#include "CommandList.h"

using namespace JFL;

namespace JFL::Private::Direct3D
{
	JFGraphicsDevice* CreateGraphicsDevice()
	{
		return new GraphicsDevice();
	}
}

GraphicsDevice::GraphicsDevice()
{
    UINT dxgiFactoryFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
    if (GraphicsOption::ENABLE_DEBUG_LAYER)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
            //JFLogInfo("Enable D3D12 debug layer.");

            // this is slow for gpu debug.
            if (GraphicsOption::ENABLE_GPU_VALIDATION)
            {
                ComPtr<ID3D12Debug1> debugController1;
                if (SUCCEEDED(debugController->QueryInterface(IID_PPV_ARGS(&debugController1))))
                {
                    debugController1->SetEnableGPUBasedValidation(true);
                    //JFLogInfo("Enable D3D12 GPU based validation.");
                }
            }
        }
        else
        {
            //JFLogWarning("Unable to enable D3D12 debug layer");
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
#endif

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
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), GraphicsOption::MIN_FEATURE, IID_PPV_ARGS(&device))))
            {
                //JFLogInfo(L"Usable hardware info: {} ({} MB)", desc.Description, desc.DedicatedVideoMemory >> 20);
                maxSize = desc.DedicatedVideoMemory;
            }
        }
    }
    if (device)
    {
        ThrowIfFailed(factory->EnumAdapterByLuid(device->GetAdapterLuid(), IID_PPV_ARGS(&adapter)));

        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        //JFLogInfo(L"Selected hardware info: {} ({} MB)", desc.Description, desc.DedicatedVideoMemory >> 20);
    }
    // software adapter.
    else
    {
        //JFLogWarning("Failed to find a supportable hardware adapter");

        ComPtr<IDXGIAdapter> warpAdapter;
        ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

        ThrowIfFailed(D3D12CreateDevice(
            warpAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&device)));

        //JFLogInfo("Instead used WARP software adapter");
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
    return new CommandQueue(this, queue.Get());
}

JFObject<JFCommandList> GraphicsDevice::CreateCommandList()
{
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ThrowIfFailed(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));

    ComPtr<ID3D12GraphicsCommandList> commandList;
    ThrowIfFailed(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));

    return new CommandList(commandAllocator.Get(), commandList.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
}
