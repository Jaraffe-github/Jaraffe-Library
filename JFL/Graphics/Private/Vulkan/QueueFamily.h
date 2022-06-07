//
//  File: QueueFamily.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "vulkan_headers.h"
#include "Object/JFRefCounter.h"
#include "Lock/JFLock.h"
#include <optional>
#include <vector>

namespace JFL::Private::Vulkan
{
	class CommandQueue;

	class QueueFamily final : public JFRefCounter
	{
	public:
		QueueFamily(VkDevice device, const VkQueueFamilyProperties& queueProperty, uint32_t familyIndex);
		~QueueFamily() = default;

		uint32_t FamilyIndex() const;
		size_t QueueCount() const;

		bool IsFlagSupported(VkQueueFlags queueFlag);

		CommandQueue* CreateCommandQueue();
		void ReleaseCommandQueue(CommandQueue* queue);

	private:
		VkQueueFamilyProperties queueProperty;
		uint32_t familyIndex;

		JFSpinLock queueLock;
		std::vector<VkQueue> usableQueues;
	};
}