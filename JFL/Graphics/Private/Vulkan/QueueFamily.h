//
//  File: QueueFamily.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "vulkan_headers.h"
#include <optional>
#include <vector>

namespace JFL::Private::Vulkan
{
	class QueueFamily final
	{
	public:
		QueueFamily(VkPhysicalDevice physicalDevice, VkQueueFlags queueFlags, uint32_t familyIndex, uint32_t queueCount, float defaultQueuePriority = 0.0f);
		~QueueFamily() = default;

		VkPhysicalDevice PhysicalDevice() const;
		uint32_t FamilyIndex() const;

		size_t QueueCount() const;
		std::optional<uint32_t> GetUsableQueueIndex();
		void ReleaseQueueIndex(uint32_t queueIndex);

		const std::vector<float>& QueuePriorities() const;
		std::vector<float>& QueuePriorities();

		bool IsFlagSupported(VkQueueFlags queueFlag);

		VkDeviceQueueCreateInfo DeviceQueueCreateInfo() const;

	private:
		VkPhysicalDevice physicalDevice;
		VkQueueFlags queueFlags;
		uint32_t familyIndex;
		std::vector<bool> usableQueues;
		std::vector<float> queuePriorities;
	};
}