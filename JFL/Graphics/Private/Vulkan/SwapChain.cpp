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
	, presentQueue(queue)
	, currentFrameBufferIndex(0)
{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = (HWND)window->PlatformHandle();
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	ThrowIfFailed(vkCreateWin32SurfaceKHR(device->Instance(), &surfaceCreateInfo, nullptr, &surface));
#endif

	VkRenderPass renderPass;

	// Attachment description.
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = VK_FORMAT_R8G8B8A8_UNORM;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	// Subpasses and attachment references.
	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	// Render pass.
	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	ThrowIfFailed(vkCreateRenderPass(device->Device(), &renderPassInfo, nullptr, &renderPass));

	VkSurfaceCapabilitiesKHR capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->PhysicalDevice(), surface, &capabilities);

	JFArray<VkSurfaceFormatKHR> formats = {
		{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR }
	};
	if (!CheckSurfaceFormatSupport(formats))
		throw std::runtime_error("surface format not supported!");

	JFArray<VkPresentModeKHR> presentModes ={
		VK_PRESENT_MODE_FIFO_KHR
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

	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0;
	createInfo.pQueueFamilyIndices = nullptr;

	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	ThrowIfFailed(vkCreateSwapchainKHR(device->Device(), &createInfo, nullptr, &swapChain));

	uint32_t imageCount;
	vkGetSwapchainImagesKHR(device->Device(), swapChain, &imageCount, nullptr);
	JFArray<VkImage> colorImages(imageCount);
	vkGetSwapchainImagesKHR(device->Device(), swapChain, &imageCount, colorImages.Data());

	colorTextures.Reserve(imageCount);
	framebuffers.Reserve(imageCount);

	// Create image view.
	for (VkImage colorImage : colorImages)
	{
		// image view.
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = colorImage;

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = VK_FORMAT_B8G8R8A8_UNORM;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		VkImageView imageView;
		ThrowIfFailed(vkCreateImageView(device->Device(), &createInfo, nullptr, &imageView));

		// frame buffer.
		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &imageView;
		framebufferInfo.width = width;
		framebufferInfo.height = height;
		framebufferInfo.layers = 1;

		VkFramebuffer frameBuffer;
		ThrowIfFailed(vkCreateFramebuffer(device->Device(), &framebufferInfo, nullptr, &frameBuffer));

		colorTextures.Add(new Texture(device, colorImage, imageView, frameBuffer));
	}

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	ThrowIfFailed(vkCreateSemaphore(device->Device(), &semaphoreInfo, nullptr, &imageAvailableSemaphore));
}

SwapChain::~SwapChain()
{
	colorTextures.Clear();

	vkDestroySemaphore(device->Device(), imageAvailableSemaphore, nullptr);
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
	return colorTextures[currentFrameBufferIndex];
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
	vkAcquireNextImageKHR(device->Device(), swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &currentFrameBufferIndex);

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 0;
	presentInfo.pWaitSemaphores = nullptr;

	VkSwapchainKHR swapChains[] = { swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &currentFrameBufferIndex;

	vkQueuePresentKHR(presentQueue->Queue(), &presentInfo);
}

bool SwapChain::CheckSurfaceFormatSupport(const JFArray<VkSurfaceFormatKHR>& surfaceFormats)
{
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->PhysicalDevice(), surface, &formatCount, nullptr);

	JFArray<VkSurfaceFormatKHR> availableFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->PhysicalDevice(), surface, &formatCount, availableFormats.Data());

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

bool SwapChain::CheckSurfacePresentMode(const JFArray<VkPresentModeKHR>& presentModes)
{
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->PhysicalDevice(), surface, &presentModeCount, nullptr);

	JFArray<VkPresentModeKHR> availablePresentModes(presentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->PhysicalDevice(), surface, &presentModeCount, availablePresentModes.Data());

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