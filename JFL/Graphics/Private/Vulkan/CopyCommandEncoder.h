//
//  File: CopyCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCopyCommandEncoder.h"
#include "vulkan_headers.h"
#include "CommandBuffer.h"

namespace JFL::Private::Vulkan
{
	class CopyCommandEncoder final : public JFCopyCommandEncoder
	{
	public:
		CopyCommandEncoder(CommandBuffer*, VkCommandBuffer);
		~CopyCommandEncoder();

		void CopyBufferToBuffer(JFGPUBuffer* src, size_t srcOffset, JFGPUBuffer* dest, size_t destOffset, size_t copySize);
		void CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea);
		void CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset);

		void EndEncoding();

		JFObject<CommandBuffer> commandBuffer;
		VkCommandBuffer vkCommandBuffer;
	};
}
