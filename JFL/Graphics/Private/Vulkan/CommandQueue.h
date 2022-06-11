//
//  File: CommandQueue.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandQueue.h"
#include "JFInclude.h"
#include "vulkan_headers.h"
#include "QueueFamily.h"
#include "GraphicsDevice.h"
#include "Object/JFObject.h"

namespace JFL::Private::Vulkan
{
	class GraphicsDevice;

	class CommandQueue final : public JFCommandQueue
	{
	public:
		CommandQueue(GraphicsDevice* device, VkQueue queue, QueueFamily* queueFamily);
		~CommandQueue();

		JFObject<JFSwapChain> CreateSwapChain(const JFWindow* window) override;
		JFObject<JFCommandBuffer> CreateCommandBuffer() override;

		void WaitComplete() override;

		VkQueue Queue() const { return queue; }

	private:
		VkQueue queue;
		JFObject<QueueFamily> queueFamily;
		JFObject<GraphicsDevice> device;
	};
}