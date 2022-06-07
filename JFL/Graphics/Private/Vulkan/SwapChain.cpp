//
//  File: SwapChain.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "SwapChain.h"
#include "GraphicsDevice.h"
#include "Window/JFWindow.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

SwapChain::SwapChain(GraphicsDevice* device, CommandQueue* queue, const JFWindow* window)
{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = (HWND)window->PlatformHandle();
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	ThrowIfFailed(vkCreateWin32SurfaceKHR(device->Instance(), &surfaceCreateInfo, nullptr, &surface));
#endif
}

uint32_t SwapChain::Width()
{
    return uint32_t();
}

uint32_t SwapChain::Height()
{
    return uint32_t();
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{
}
