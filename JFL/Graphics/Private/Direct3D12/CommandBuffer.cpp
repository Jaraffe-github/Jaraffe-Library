//
//  File: CommandBuffer.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandBuffer.h"
#include "CopyCommandEncoder.h"
#include "RenderCommandEncoder.h"
#include "RenderPipeline.h"
#include "GraphicsDevice.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

CommandBuffer::CommandBuffer(GraphicsDevice* device, CommandQueue* queue, CommandAllocator* allocator)
	: device(device)
	, queue(queue)
	, allocator(allocator)
	, encodedCommandList()
{
}

CommandBuffer::~CommandBuffer() noexcept
{
	JFASSERT_DEBUG(device);

	for (const ComPtr<ID3D12GraphicsCommandList>& list : encodedCommandList)
		device->ReleaseCommandList(list.Get());
	encodedCommandList.Clear();

	device->ReleaseCommandAllocator(allocator);
}

JFObject<JFRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(JFRenderPipeline* pipelineState)
{
	if (RenderPipeline* ps = dynamic_cast<RenderPipeline*>(pipelineState))
	{
		if (ComPtr<ID3D12GraphicsCommandList> commandList = device->GetCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT))
		{
			commandList->Reset(allocator->Allocator(), ps->PipelineState());
			return new RenderCommandEncoder(ps, this, commandList.Get());
		}
	}
	return nullptr;
}

JFObject<JFCopyCommandEncoder> CommandBuffer::CreateCopyCommandEncoder()
{
	if (ComPtr<ID3D12GraphicsCommandList> commandList = device->GetCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT))
	{
		commandList->Reset(allocator->Allocator(), nullptr);
		return new CopyCommandEncoder(this, commandList.Get());
	}
	return nullptr;
}

void CommandBuffer::Commit()
{
	if (encodedCommandList.Count() > 0 && allocator->IsUsable())
	{
		uint64_t committedFenceNumber = queue->ExecuteCommandLists(static_cast<UINT>(encodedCommandList.Count()),
																   reinterpret_cast<ID3D12CommandList* const*>(encodedCommandList.Data()));
		allocator->SetCommittedState(queue->Fence(), committedFenceNumber);
	}
}

void CommandBuffer::AddEncodedCommandList(ID3D12GraphicsCommandList* commandList)
{
	encodedCommandList.Add(commandList);
}

