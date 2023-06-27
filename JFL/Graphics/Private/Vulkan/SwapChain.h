//
//  File: QueueFamily.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFSwapChain.h"
#include "JFInclude.h"
#include "vulkan_headers.h"
#include "GraphicsDevice.h"
#include "Texture.h"

namespace JFL::Private::Vulkan
{
	class CommandQueue;
	class GraphicsDevice;

	class SwapChain final : public JFSwapChain
	{
	public:
		SwapChain(GraphicsDevice* device, CommandQueue* queue, QueueFamily* queueFamily, const JFWindow* window);
		~SwapChain();

		uint32_t Width() override;
		uint32_t Height() override;

		const JFTexture* CurrentColorTexture() const override;
		const JFTexture* DepthStencilTexture() const override;

		void Resize(uint32_t width, uint32_t height) override;
		void Present() override;

	private:
		bool CheckSurfaceFormatSupport(const JFArray<VkSurfaceFormatKHR>& surfaceFormats);
		bool CheckSurfacePresentMode(const JFArray<VkPresentModeKHR>& presentModes);

		VkSurfaceKHR surface;
		VkSwapchainKHR swapChain;

		JFArray<Texture> colorTextures;

		uint32_t width;
		uint32_t height;
		JFObject<GraphicsDevice> device;
	};
}