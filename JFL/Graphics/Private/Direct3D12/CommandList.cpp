//
//  File: CommandList.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandList.h"

using namespace JFL;

CommandList::CommandList(ID3D12CommandAllocator* allocator, ID3D12CommandList* list, D3D12_COMMAND_LIST_TYPE type)
	: type(type)
	, list(list)
	, allocator(allocator)
{
}

void CommandList::Reset()
{
	ThrowIfFailed(allocator->Reset());
}
