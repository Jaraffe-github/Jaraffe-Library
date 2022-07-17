//
//  File: CommandAllocator.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandAllocator.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

CommandAllocator::CommandAllocator(ID3D12CommandAllocator* allocator, D3D12_COMMAND_LIST_TYPE type)
	: type(type)
	, allocator(allocator)
	, committedCounter(0)
{
}

void CommandAllocator::SetCommittedState(ID3D12Fence* fence, uint64_t committedCounter)
{
	this->fence = fence;
	this->committedCounter = committedCounter;
}

bool CommandAllocator::IsUsable() const
{
	if (fence)
		return fence->GetCompletedValue() >= committedCounter;
	return true;
}

void CommandAllocator::Reset()
{
	ThrowIfFailed(allocator->Reset());
}
