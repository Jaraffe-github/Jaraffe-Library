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
		CommandBuffer(CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, D3D12_COMMAND_LIST_TYPE);
		~CommandBuffer() noexcept = default;

		JFObject<JFRenderCommandEncoder> CreateRenderCommandEncoder(JFRenderPipeline* pipelineState) override;
		JFObject<JFCopyCommandEncoder> CreateCopyCommandEncoder() override;

		void Commit() override;

		void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

	private:
		std::vector<ComPtr<ID3D12GraphicsCommandList>> encodedCommandList;

		D3D12_COMMAND_LIST_TYPE type;
		JFObject<CommandQueue> commandQueue;
		ComPtr<ID3D12GraphicsCommandList> list;
		ComPtr<ID3D12CommandAllocator> allocator;
	};

}
