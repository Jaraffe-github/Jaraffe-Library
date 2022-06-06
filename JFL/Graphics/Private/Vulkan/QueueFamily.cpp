//
//  File: QueueFamily.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "QueueFamily.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

QueueFamily::QueueFamily(VkPhysicalDevice physicalDevice, VkQueueFlags queueFlags, uint32_t familyIndex, uint32_t queueCount, float defaultQueuePriority)
	: physicalDevice(physicalDevice)
	, queueFlags(queueFlags)
	, familyIndex(familyIndex)
	, usableQueues(queueCount, true)
	, queuePriorities(queueCount, defaultQueuePriority)
{
}

bool QueueFamily::IsFlagSupported(VkQueueFlags queueFlag)
{
	return this->queueFlags & queueFlag;
}

VkPhysicalDevice QueueFamily::PhysicalDevice() const
{
	return physicalDevice;
}

uint32_t QueueFamily::FamilyIndex() const
{
	return familyIndex;
}

size_t QueueFamily::QueueCount() const
{
	return usableQueues.size();
}

std::optional<uint32_t> QueueFamily::GetUsableQueueIndex()
{
	for (int i = 0; i < usableQueues.size(); ++i)
	{
		if (usableQueues[i])
		{
			usableQueues[i] = false;
			return i;
		}
	}
	return std::nullopt;
}

void QueueFamily::ReleaseQueueIndex(uint32_t queueIndex)
{
	JFASSERT(usableQueues.size() > queueIndex);
	usableQueues[queueIndex] = true;
}

const std::vector<float>& QueueFamily::QueuePriorities() const
{
	return queuePriorities;
}

std::vector<float>& QueueFamily::QueuePriorities()
{
	return queuePriorities;
}

VkDeviceQueueCreateInfo QueueFamily::DeviceQueueCreateInfo() const
{
	VkDeviceQueueCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	createInfo.queueFamilyIndex = familyIndex;
	createInfo.queueCount = static_cast<uint32_t>(usableQueues.size());
	createInfo.pQueuePriorities = queuePriorities.data();
	return createInfo;
}
