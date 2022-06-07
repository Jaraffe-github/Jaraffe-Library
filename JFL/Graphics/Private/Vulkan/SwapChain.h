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

namespace JFL::Private::Vulkan
{
	class CommandQueue;
	class GraphicsDevice;

	class SwapChain final : public JFSwapChain
	{
	public:
		SwapChain(GraphicsDevice* device, CommandQueue* queue, const JFWindow* window);
		~SwapChain() = default;

		uint32_t Width() override;
		uint32_t Height() override;
		void Resize(uint32_t width, uint32_t height) override;

	private:
		VkSurfaceKHR surface;
	};
}