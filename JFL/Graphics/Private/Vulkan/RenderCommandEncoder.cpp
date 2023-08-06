//
//  File: RenderCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#include "RenderCommandEncoder.h"
#include "Texture.h"
#include "GPUBuffer.h"
#include "VulkanUtils.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

RenderCommandEncoder::RenderCommandEncoder(RenderPipeline* renderPipeline, CommandBuffer* commandBuffer, VkCommandBuffer vkCommandBuffer)
	: renderPipeline(renderPipeline)
	, commandBuffer(commandBuffer)
	, vkCommandBuffer(vkCommandBuffer)
{
}

RenderCommandEncoder::~RenderCommandEncoder()
{
}

void RenderCommandEncoder::SetViewport(const JFViewport& viewport)
{
	this->viewport = viewport;

	VkViewport vkViewport{};
	vkViewport.x = viewport.x;
	vkViewport.y = viewport.y;
	vkViewport.width = viewport.width;
	vkViewport.height = viewport.height;
	vkViewport.minDepth = viewport.nearDepth;
	vkViewport.maxDepth = viewport.farDepth;

	commandFunctions.Add([vkViewport](VkCommandBuffer vkCommandBuffer)
	{
		vkCmdSetViewport(vkCommandBuffer, 0, 1, &vkViewport);
	});
}

void RenderCommandEncoder::SetViewports(const JFViewport* viewports, uint32_t count)
{

}

void RenderCommandEncoder::SetScissorRect(const JFRect& rect)
{
	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = VkExtent2D{ (uint32_t)rect.width, (uint32_t)rect.height };

	commandFunctions.Add([scissor](VkCommandBuffer vkCommandBuffer)
	{
		vkCmdSetScissor(vkCommandBuffer, 0, 1, &scissor);
	});
}

void RenderCommandEncoder::SetScissorRects(const JFRect* rects, uint32_t count)
{

}

void RenderCommandEncoder::SetRenderTargets(std::vector<const JFTexture*> renderTargets, const JFTexture* depthStencil)
{
	for (const JFTexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
		JFASSERT_DEBUG(rt);

		frameBuffer = rt->FrameBuffer();
	}
}

void RenderCommandEncoder::ClearRenderTargetView(const JFTexture* renderTarget, const JFLinearColor& clearColor)
{

}

void RenderCommandEncoder::ClearDepthStencilView(const JFTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil)
{

}

void RenderCommandEncoder::SetVertexBuffer(const JFGPUBuffer* vertexBuffer, uint32_t vertexSize)
{
	commandFunctions.Add([vertexBuffer, vertexSize](VkCommandBuffer vkCommandBuffer)
	{
		const GPUBuffer* vb = dynamic_cast<const GPUBuffer*>(vertexBuffer);
		JFASSERT_DEBUG(vb);

		VkBuffer vertexBuffers[] = { vb->Buffer() };
		VkDeviceSize offsets[] = { 0 };

		vkCmdBindVertexBuffers(vkCommandBuffer, 0, 1, vertexBuffers, offsets);
	});
}

void RenderCommandEncoder::SetIndexBuffer(const JFGPUBuffer* indexBuffer, uint32_t indexSize)
{

}

void RenderCommandEncoder::SetConstantBuffer(uint32_t index, const JFGPUBuffer* constantBuffer)
{

}

void RenderCommandEncoder::DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart)
{
	commandFunctions.Add([vertexCount, instanceCount, vertexStart, instanceStart](VkCommandBuffer vkCommandBuffer)
	{
		vkCmdDraw(vkCommandBuffer, vertexCount, instanceCount, vertexStart, instanceStart);
	});
}

void RenderCommandEncoder::DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart)
{

}

void RenderCommandEncoder::EndEncoding()
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	ThrowIfFailed(vkBeginCommandBuffer(vkCommandBuffer, &beginInfo));

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPipeline->RenderPass();
	renderPassInfo.framebuffer = frameBuffer;

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = VkExtent2D{ (uint32_t)viewport.width, (uint32_t)viewport.height };

	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(vkCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, renderPipeline->Pipeline());

	for (int i = 0; i < commandFunctions.Count(); ++i)
	{
		commandFunctions[i](vkCommandBuffer);
	}
	commandFunctions.Clear();

	vkCmdEndRenderPass(vkCommandBuffer);
	
	ThrowIfFailed(vkEndCommandBuffer(vkCommandBuffer));

	commandBuffer->AddEncodedCommandBuffer(vkCommandBuffer);
}
