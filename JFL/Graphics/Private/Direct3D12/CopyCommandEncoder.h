//
//  File: CopyCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCopyCommandEncoder.h"
#include "d3d12_headers.h"
#include "CommandBuffer.h"

namespace JFL::Private::Direct3D12
{
	class CopyCommandEncoder final : public JFCopyCommandEncoder
	{
	public:
		CopyCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
		~CopyCommandEncoder() = default;

		void CopyBufferToBuffer(JFGPUBuffer* src, size_t srcOffset, JFGPUBuffer* dest, size_t destOffset, size_t copySize);
		void CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea);
		void CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset);

		void EndEncoding();

	private:
		void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

		JFObject<CommandBuffer> commandBuffer;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}