//
//  File: CopyCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#include "CopyCommandEncoder.h"
#include "GPUBuffer.h"
#include "VulkanUtils.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

CopyCommandEncoder::CopyCommandEncoder(CommandBuffer* commandBuffer, VkCommandBuffer vkCommandBuffer)
	: commandBuffer(commandBuffer)
	, vkCommandBuffer(vkCommandBuffer)
{
}

CopyCommandEncoder::~CopyCommandEncoder()
{

}

void CopyCommandEncoder::CopyBufferToBuffer(JFGPUBuffer* src, size_t srcOffset, JFGPUBuffer* dest, size_t destOffset, size_t copySize)
{
	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = srcOffset;
	copyRegion.dstOffset = destOffset;
	copyRegion.size = copySize;

	commandFunctions.Add([copyRegion, src, dest](VkCommandBuffer vkCommandBuffer)
	{
		const GPUBuffer* srcBuffer = dynamic_cast<const GPUBuffer*>(src);
		JFASSERT_DEBUG(srcBuffer);

		const GPUBuffer* destBuffer = dynamic_cast<const GPUBuffer*>(dest);
		JFASSERT_DEBUG(destBuffer);

		vkCmdCopyBuffer(vkCommandBuffer, srcBuffer->Buffer(), destBuffer->Buffer(), 1, &copyRegion);
	});
}

void CopyCommandEncoder::CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea)
{

}

void CopyCommandEncoder::CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset)
{

}

void CopyCommandEncoder::EndEncoding()
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(vkCommandBuffer, &beginInfo);

	for (int i = 0; i < commandFunctions.Count(); ++i)
	{
		commandFunctions[i](vkCommandBuffer);
	}
	commandFunctions.Clear();

	ThrowIfFailed(vkEndCommandBuffer(vkCommandBuffer));

	commandBuffer->AddEncodedCommandBuffer(vkCommandBuffer);
}
