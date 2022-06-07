//
//  File: QueueFamily.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "QueueFamily.h"
#include "CommandQueue.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

QueueFamily::QueueFamily(VkDevice device, const VkQueueFamilyProperties& queueProperty, uint32_t familyIndex)
	: queueProperty(queueProperty)
	, familyIndex(familyIndex)
{
	JFScopedLock guard(queueLock);
	usableQueues.resize(queueProperty.queueCount);
	for (uint32_t i = 0; i < queueProperty.queueCount; ++i)
	{
		vkGetDeviceQueue(device, familyIndex, i, &usableQueues[i]);
		JFASSERT(usableQueues[i]);
	}
}

bool QueueFamily::IsFlagSupported(VkQueueFlags queueFlag)
{
	return queueProperty.queueFlags & queueFlag;
}

CommandQueue* QueueFamily::CreateCommandQueue(GraphicsDevice* device)
{
	JFScopedLock guard(queueLock);
	if (usableQueues.size() > 0)
	{
		VkQueue& queue = usableQueues.back();
		usableQueues.pop_back();
		guard.Unlock();

		return new CommandQueue(device, queue, this);
	}
	JFASSERT(false);
	return nullptr;
}

void QueueFamily::ReleaseCommandQueue(CommandQueue* queue)
{
	JFScopedLock guard(queueLock);
	usableQueues.push_back(queue->Queue());
}

uint32_t QueueFamily::FamilyIndex() const
{
	return familyIndex;
}

size_t QueueFamily::QueueCount() const
{
	return queueProperty.queueCount;
}
