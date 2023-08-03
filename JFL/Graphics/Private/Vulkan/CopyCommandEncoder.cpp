//
//  File: CopyCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#include "CopyCommandEncoder.h"

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

}

void CopyCommandEncoder::CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea)
{

}

void CopyCommandEncoder::CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset)
{

}

void CopyCommandEncoder::EndEncoding()
{

}
