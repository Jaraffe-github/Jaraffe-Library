//
//  File: SwapChain.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "SwapChain.h"
#include "GraphicsDevice.h"
#include "Window/JFWindow.h"
#include "SwapChain.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

SwapChain::SwapChain(GraphicsDevice* device, CommandQueue* queue, QueueFamily* queueFamily, const JFWindow* window)
	: width(window->Width())
	, height(window->Height())
	, device(device)
{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = (HWND)window->PlatformHandle();
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	ThrowIfFailed(vkCreateWin32SurfaceKHR(device->Instance(), &surfaceCreateInfo, nullptr, &surface));
#endif

	VkSurfaceCapabilitiesKHR capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->PhysicalDevice(), surface, &capabilities);

	std::vector<VkSurfaceFormatKHR> formats = {
		{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR }
	};
	if (!CheckSurfaceFormatSupport(formats))
		throw std::runtime_error("surface format not supported!");

	std::vector<VkPresentModeKHR> presentModes ={
		VK_PRESENT_MODE_MAILBOX_KHR
	};
	if (!CheckSurfacePresentMode(presentModes))
		throw std::runtime_error("surface present mode not supported!");

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;

	createInfo.minImageCount = capabilities.maxImageCount;
	createInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	createInfo.imageExtent = VkExtent2D(width, height);
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	uint32_t queueFamilyIndices[] = { queueFamily->FamilyIndex() };
	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	//createInfo.queueFamilyIndexCount = 1;
	//createInfo.pQueueFamilyIndices = queueFamilyIndices;

	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	ThrowIfFailed(vkCreateSwapchainKHR(device->Device(), &createInfo, nullptr, &swapChain));

	uint32_t imageCount;
	vkGetSwapchainImagesKHR(device->Device(), swapChain, &imageCount, nullptr);
	colorImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device->Device(), swapChain, &imageCount, colorImages.data());
}

SwapChain::~SwapChain()
{
	vkDestroySwapchainKHR(device->Device(), swapChain, nullptr);
	vkDestroySurfaceKHR(device->Instance(), surface, nullptr);
}

uint32_t SwapChain::Width()
{
    return width;
}

uint32_t SwapChain::Height()
{
    return height;
}

const JFTexture* SwapChain::CurrentColorTexture() const
{
	return nullptr;
}

const JFTexture* SwapChain::DepthStencilTexture() const
{
	return nullptr;
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{
}

void SwapChain::Present()
{

}

bool SwapChain::CheckSurfaceFormatSupport(const std::vector<VkSurfaceFormatKHR>& surfaceFormats)
{
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->PhysicalDevice(), surface, &formatCount, nullptr);

	std::vector<VkSurfaceFormatKHR> availableFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->PhysicalDevice(), surface, &formatCount, availableFormats.data());

	for (const VkSurfaceFormatKHR& surfaceFormat : surfaceFormats)
	{
		if (std::find_if(availableFormats.begin(),
						 availableFormats.end(),
						 [surfaceFormat](VkSurfaceFormatKHR other)
						 {
							 return surfaceFormat.format == other.format && surfaceFormat.colorSpace == other.colorSpace;
						 }) != availableFormats.end())
		{
			JFLogInfo("Supported surface format number : {}", (int)surfaceFormat.format);
		}
		else
		{
			JFLogWarning("Not supported surface format number: {}", (int)surfaceFormat.format);
			return false;
		}
	}
	return true;
}

bool SwapChain::CheckSurfacePresentMode(const std::vector<VkPresentModeKHR>& presentModes)
{
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->PhysicalDevice(), surface, &presentModeCount, nullptr);

	std::vector<VkPresentModeKHR> availablePresentModes(presentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->PhysicalDevice(), surface, &presentModeCount, availablePresentModes.data());

	for (const VkPresentModeKHR& presentMode : presentModes)
	{
		if (std::find_if(availablePresentModes.begin(),
						 availablePresentModes.end(),
						 [presentMode](VkPresentModeKHR other)
						 {
							 return presentMode == other;
						 }) != availablePresentModes.end())
		{
			JFLogInfo("Supported present mode number : {}", (int)presentMode);
		}
		else
		{
			JFLogWarning("Not supported present mode number: {}", (int)presentMode);
			return false;
		}
	}
	return true;
}