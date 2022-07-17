//
//  File: CommandAllocator.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "d3d12_headers.h"
#include "Object/JFObject.h"

namespace JFL::Private::Direct3D12
{
    class CommandAllocator : public JFRefCounter
    {
    public:
        CommandAllocator(ID3D12CommandAllocator* allocator, D3D12_COMMAND_LIST_TYPE type);
        ~CommandAllocator() = default;

        void SetCommittedState(ID3D12Fence* fence, uint64_t committedCounter);
        bool IsUsable() const;
        void Reset();

        ID3D12CommandAllocator* Allocator() const { return allocator.Get(); }
        D3D12_COMMAND_LIST_TYPE Type() const { return type; }

    private:
        uint64_t committedCounter;
        ComPtr<ID3D12Fence> fence;
        D3D12_COMMAND_LIST_TYPE type;
        ComPtr<ID3D12CommandAllocator> allocator;
    };
}
