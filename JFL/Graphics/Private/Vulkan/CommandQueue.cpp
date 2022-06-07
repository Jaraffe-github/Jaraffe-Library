//
//  File: CommandQueue.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandQueue.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

CommandQueue::CommandQueue(VkQueue queue, QueueFamily* queueFamily)
	: queue(queue)
	, queueFamily(queueFamily)
{
}

CommandQueue::~CommandQueue()
{
	queueFamily->ReleaseCommandQueue(this);
}

JFObject<JFSwapChain> CommandQueue::CreateSwapChain(const JFWindow* window)
{
	return nullptr;
}