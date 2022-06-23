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

CommandBuffer::CommandBuffer(CommandQueue* commandQueue, ID3D12CommandAllocator* allocator, ID3D12GraphicsCommandList* list, D3D12_COMMAND_LIST_TYPE type)
	: type(type)
	, commandQueue(commandQueue)
	, list(list)
	, allocator(allocator)
{
}

JFObject<JFRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(JFRenderPipeline* pipelineState)
{
	if (RenderPipeline* ps = dynamic_cast<RenderPipeline*>(pipelineState))
	{
		list->Reset(allocator.Get(), ps->PipelineState());
	}
	else
	{
		list->Reset(allocator.Get(), nullptr);
	}
	return new RenderCommandEncoder(this, list.Get());
}

JFObject<JFCopyCommandEncoder> CommandBuffer::CreateCopyCommandEncoder()
{
	list->Reset(allocator.Get(), nullptr);
	return new CopyCommandEncoder(this, list.Get());
}

void CommandBuffer::Commit()
{
	ID3D12CommandList* cmdLists[] = { list.Get() };
	commandQueue->ExecuteCommandLists(1, cmdLists);
}

void CommandBuffer::AddEncodedCommandList(ID3D12GraphicsCommandList* commandList)
{
	// not yet.
}

