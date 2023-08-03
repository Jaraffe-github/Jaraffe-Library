//
//  File: CommandBuffer.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#include "CommandBuffer.h"
#include "CopyCommandEncoder.h"
#include "RenderCommandEncoder.h"
#include "RenderPipeline.h"
#include "GraphicsDevice.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

CommandBuffer::CommandBuffer(GraphicsDevice* device, CommandQueue* queue, VkCommandPool commandPool)
	: device(device)
	, queue(queue)
	, commandPool(commandPool)
{
}

CommandBuffer::~CommandBuffer() noexcept
{
	JFASSERT_DEBUG(device);

	if (commandPool)
	{
		vkDestroyCommandPool(device->Device(), commandPool, nullptr);
	}
}

JFObject<JFRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(JFRenderPipeline* pipelineState)
{
	if (RenderPipeline* ps = dynamic_cast<RenderPipeline*>(pipelineState))
	{
		VkCommandBuffer commandBuffer = GetCommandBuffer();
		if (commandBuffer)
		{
			vkResetCommandBuffer(commandBuffer, 0);
			return new RenderCommandEncoder(ps, this, commandBuffer);
		}
	}
	return nullptr;
}

JFObject<JFCopyCommandEncoder> CommandBuffer::CreateCopyCommandEncoder()
{
	VkCommandBuffer commandBuffer = GetCommandBuffer();
	if (commandBuffer)
	{
		vkResetCommandBuffer(commandBuffer, 0);
		return new CopyCommandEncoder(this, commandBuffer);
	}
	return nullptr;
}

void CommandBuffer::Commit()
{
	// temp process.
	JFArray<VkSubmitInfo> submitInfos;
	
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 0;
	submitInfo.pWaitSemaphores = nullptr;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = encodedCommandBuffers.Count();
	submitInfo.pCommandBuffers = encodedCommandBuffers.Data();

	submitInfo.signalSemaphoreCount = 0;
	submitInfo.pSignalSemaphores = nullptr;
	submitInfos.Add(submitInfo);

	queue->Submit(submitInfos.Data(), submitInfos.Count());
}

VkCommandBuffer CommandBuffer::GetCommandBuffer()
{
	if (commandBuffers.Count() > 0)
	{
		VkCommandBuffer commandBuffer = commandBuffers.Back();
		commandBuffers.Remove(commandBuffers.Count() - 1);

		return commandBuffer;
	}

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer newCommandBuffer;
	ThrowIfFailed(vkAllocateCommandBuffers(device->Device(), &allocInfo, &newCommandBuffer));

	return newCommandBuffer;
}

void CommandBuffer::ReleaseCommandBuffer(VkCommandBuffer commandBuffer)
{
	commandBuffers.Add(commandBuffer);
}

void CommandBuffer::AddEncodedCommandBuffer(VkCommandBuffer commandBuffer)
{
	encodedCommandBuffers.Add(commandBuffer);
}
