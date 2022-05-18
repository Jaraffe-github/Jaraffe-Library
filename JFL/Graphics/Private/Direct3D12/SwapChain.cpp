//
//  File: SwapChain.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "SwapChain.h"
#include "Window/JFWindow.h"
#include "CommandQueue.h"

using namespace JFL;

SwapChain::SwapChain(GraphicsDevice* device, CommandQueue* queue, const JFWindow* window)
	: width(window->Width())
	, height(window->Height())
	, currentColorTextureIndex(0)
	, swapChain(nullptr)
	, device(nullptr)
{
    DXGI_SWAP_CHAIN_DESC1 desc{};
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferCount = FRAME_BUFFER_COUNT;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ComPtr<IDXGISwapChain1> swapChain1;
    ThrowIfFailed(device->Factory()->CreateSwapChainForHwnd(
        queue->Queue(),
        reinterpret_cast<HWND>(window->PlatformHandle()),
        &desc,
        nullptr,
        nullptr,
        swapChain1.GetAddressOf()));

    ThrowIfFailed(swapChain1.As(&swapChain));
    currentColorTextureIndex = swapChain->GetCurrentBackBufferIndex();

    for (UINT i = 0; i < FRAME_BUFFER_COUNT; ++i)
        ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&colorTexture[i])));
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{
    if (this->width != width || this->height != height)
    {
        this->width = width;
        this->height = height;

        // Clear resources
        for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
            colorTexture[i] = nullptr;
        depthStencilTexture = nullptr;

        DXGI_SWAP_CHAIN_DESC desc{};
        swapChain->GetDesc(&desc);
        ThrowIfFailed(swapChain->ResizeBuffers(
            FRAME_BUFFER_COUNT,
            width, height,
            desc.BufferDesc.Format,
            desc.Flags));

        // Reset the frame index to the current back buffer index.
        currentColorTextureIndex = swapChain->GetCurrentBackBufferIndex();

        for (UINT i = 0; i < FRAME_BUFFER_COUNT; ++i)
            ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&colorTexture[i])));
    }
}
