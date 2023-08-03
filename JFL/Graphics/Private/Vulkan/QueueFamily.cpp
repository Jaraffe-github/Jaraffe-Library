//
//  File: QueueFamily.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "QueueFamily.h"
#include "CommandQueue.h"
#include "GraphicsDevice.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

QueueFamily::QueueFamily(GraphicsDevice* device, const VkQueueFamilyProperties& queueProperty, uint32_t familyIndex)
	: queueProperty(queueProperty)
	, familyIndex(familyIndex)
{
	JFScopedLock guard(queueLock);
	usableQueues.Add(VkQueue{}, queueProperty.queueCount);
	for (uint32_t i = 0; i < queueProperty.queueCount; ++i)
	{
		vkGetDeviceQueue(device->Device(), familyIndex, i, &usableQueues[i]);
		JFASSERT(usableQueues[i]);
	}
}

QueueFamily::~QueueFamily()
{
}

bool QueueFamily::IsFlagSupported(VkQueueFlags queueFlag)
{
	return queueProperty.queueFlags & queueFlag;
}

CommandQueue* QueueFamily::CreateCommandQueue(GraphicsDevice* device)
{
	JFScopedLock guard(queueLock);
	if (usableQueues.Count() > 0)
	{
		VkQueue& queue = usableQueues.Back();
		usableQueues.PopBack();
		guard.Unlock();

		return new CommandQueue(device, queue, this);
	}
	JFASSERT(false);
	return nullptr;
}

void QueueFamily::ReleaseCommandQueue(CommandQueue* queue)
{
	JFScopedLock guard(queueLock);
	usableQueues.Add(queue->Queue());
}

uint32_t QueueFamily::FamilyIndex() const
{
	return familyIndex;
}

size_t QueueFamily::QueueCount() const
{
	return queueProperty.queueCount;
}
