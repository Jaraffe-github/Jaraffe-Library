//
//  File: CommandQueue.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandQueue.h"
#include "SwapChain.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

CommandQueue::CommandQueue(GraphicsDevice* device, VkQueue queue, QueueFamily* queueFamily)
	: device(device)
	, queue(queue)
	, queueFamily(queueFamily)
{
}

CommandQueue::~CommandQueue()
{
	queueFamily->ReleaseCommandQueue(this);
}

JFObject<JFSwapChain> CommandQueue::CreateSwapChain(const JFWindow* window)
{
	return new SwapChain(device, this, window);
}