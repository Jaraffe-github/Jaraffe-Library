//
//  File: CommandBuffer.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandBuffer.h"
#include "RenderCommandEncoder.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

CommandBuffer::CommandBuffer(CommandQueue* commandQueue, ID3D12CommandAllocator* allocator, ID3D12GraphicsCommandList* list, D3D12_COMMAND_LIST_TYPE type)
	: type(type)
	, commandQueue(commandQueue)
	, list(list)
	, allocator(allocator)
{
}

JFObject<JFRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder()
{
	list->Reset(allocator.Get(), nullptr);
	return new RenderCommandEncoder(this, list.Get());
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

