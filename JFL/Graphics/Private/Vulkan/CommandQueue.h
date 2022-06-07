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
#include "Object/JFObject.h"

namespace JFL::Private::Vulkan
{
	class CommandQueue final : public JFCommandQueue
	{
	public:
		CommandQueue(VkQueue queue, QueueFamily* queueFamily);
		~CommandQueue();

		VkQueue Queue() const { return queue; }

		JFObject<JFSwapChain> CreateSwapChain(const JFWindow* window) override;

	private:
		VkQueue queue;
		JFObject<QueueFamily> queueFamily;
	};
}