//
//  File: CommandQueue.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandBuffer.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

CommandQueue::CommandQueue(GraphicsDevice* device, VkQueue queue, QueueFamily* queueFamily)
	: device(device)
	, queue(queue)
	, queueFamily(queueFamily)
{
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	ThrowIfFailed(vkCreateFence(device->Device(), &fenceInfo, nullptr, &fence));
}

CommandQueue::~CommandQueue()
{
	vkDestroyFence(device->Device(), fence, nullptr);
}

JFObject<JFSwapChain> CommandQueue::CreateSwapChain(const JFWindow* window)
{
	return new SwapChain(device, this, queueFamily, window);
}

JFObject<JFCommandBuffer> CommandQueue::CreateCommandBuffer()
{
	VkCommandPoolCreateInfo commandPoolCreateInfo{};
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamily->FamilyIndex());

	VkCommandPool commandPool;
	ThrowIfFailed(vkCreateCommandPool(device->Device(), &commandPoolCreateInfo, nullptr, &commandPool));

	return new CommandBuffer(device, this, commandPool);
}

void CommandQueue::WaitComplete()
{
	vkWaitForFences(device->Device(), 1, &fence, VK_TRUE, UINT64_MAX);
	vkResetFences(device->Device(), 1, &fence);
}

void CommandQueue::Submit(const VkSubmitInfo* submitInfos, uint32_t numSubmitInfos)
{
	ThrowIfFailed(vkQueueSubmit(queue, numSubmitInfos, submitInfos, fence));
}