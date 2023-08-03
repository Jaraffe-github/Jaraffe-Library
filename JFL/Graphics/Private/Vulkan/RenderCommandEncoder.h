//
//  File: RenderCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFRenderCommandEncoder.h"
#include "vulkan_headers.h"
#include "CommandBuffer.h"
#include "RenderPipeline.h"
#include <functional>

namespace JFL::Private::Vulkan
{
	class RenderCommandEncoder final : public JFRenderCommandEncoder
	{
	public:
		RenderCommandEncoder(RenderPipeline*, CommandBuffer*, VkCommandBuffer);
		~RenderCommandEncoder();

		void SetViewport(const JFViewport& viewport) override;
		void SetViewports(const JFViewport* viewports, uint32_t count) override;
		void SetScissorRect(const JFRect& rect) override;
		void SetScissorRects(const JFRect* rects, uint32_t count) override;

		void SetRenderTargets(std::vector<const JFTexture*> renderTargets, const JFTexture* depthStencil) override;

		void ClearRenderTargetView(const JFTexture* renderTarget, const JFLinearColor& clearColor) override;
		void ClearDepthStencilView(const JFTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;

		void SetVertexBuffer(const JFGPUBuffer* vertexBuffer, uint32_t vertexSize) override;
		void SetIndexBuffer(const JFGPUBuffer* indexBuffer, uint32_t indexSize) override;

		void SetConstantBuffer(uint32_t index, const JFGPUBuffer* constantBuffer) override;

		void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) override;
		void DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart) override;

		void EndEncoding() override;

		JFObject<RenderPipeline> renderPipeline;
		JFObject<CommandBuffer> commandBuffer;
		VkCommandBuffer vkCommandBuffer;

		JFViewport viewport;
		VkFramebuffer frameBuffer;

		JFArray<std::function<void(VkCommandBuffer)>> commandFunctions;
	};
}
