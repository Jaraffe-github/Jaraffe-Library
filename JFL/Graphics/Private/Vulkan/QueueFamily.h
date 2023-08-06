//
//  File: QueueFamily.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "VulkanHeaders.h"
#include "Object/JFObject.h"
#include "Object/JFRefCounter.h"
#include "Lock/JFLock.h"
#include "Container/JFArray.h"

namespace JFL::Private::Vulkan
{
	class CommandQueue;
	class GraphicsDevice;

	class QueueFamily final : public JFRefCounter
	{
	public:
		QueueFamily(GraphicsDevice* device, const VkQueueFamilyProperties& queueProperty, uint32_t familyIndex);
		~QueueFamily();

		uint32_t FamilyIndex() const;
		size_t QueueCount() const;

		bool IsFlagSupported(VkQueueFlags queueFlag);

		CommandQueue* CreateCommandQueue(GraphicsDevice* device);
		void ReleaseCommandQueue(CommandQueue* queue);

	private:
		uint32_t familyIndex;
		VkQueueFamilyProperties queueProperty;

		JFSpinLock queueLock;
		JFArray<VkQueue> usableQueues;
	};
}