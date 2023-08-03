//
//  File: CommandBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandBuffer.h"
#include "vulkan_headers.h"
#include "CommandQueue.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Vulkan
{
	class CommandBuffer final : public JFCommandBuffer
	{
	public:
		CommandBuffer(GraphicsDevice* device, CommandQueue* queue, VkCommandPool commandPool);
		~CommandBuffer() noexcept;

		JFObject<JFRenderCommandEncoder> CreateRenderCommandEncoder(JFRenderPipeline* pipelineState) override;
		JFObject<JFCopyCommandEncoder> CreateCopyCommandEncoder() override;

		void Commit() override;

		VkCommandBuffer GetCommandBuffer();
		void ReleaseCommandBuffer(VkCommandBuffer commandBuffer);
		void AddEncodedCommandBuffer(VkCommandBuffer commandBuffer);

	private:
		JFObject<GraphicsDevice> device;
		JFObject<CommandQueue> queue;

		VkCommandPool commandPool;
		JFArray<VkCommandBuffer> commandBuffers;
		JFArray<VkCommandBuffer> encodedCommandBuffers;
	};
}
