//
//  File: CommandBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandBuffer.h"
#include "d3d12_headers.h"
#include "CommandQueue.h"

namespace JFL::Private::Direct3D12
{
	class CommandBuffer final : public JFCommandBuffer
	{
	public:
		CommandBuffer(GraphicsDevice*, CommandQueue*, CommandAllocator*);
		~CommandBuffer() noexcept;

		JFObject<JFRenderCommandEncoder> CreateRenderCommandEncoder(JFRenderPipeline* pipelineState) override;
		JFObject<JFCopyCommandEncoder> CreateCopyCommandEncoder() override;

		void Commit() override;

		void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

	private:
		JFArray<ComPtr<ID3D12GraphicsCommandList>> encodedCommandList;

		JFObject<GraphicsDevice> device;
		JFObject<CommandQueue> queue;
		JFObject<CommandAllocator> allocator;
	};

}
