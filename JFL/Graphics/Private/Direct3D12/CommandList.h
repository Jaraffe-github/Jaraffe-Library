//
//  File: CommandList.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandList.h"
#include "d3d12_headers.h"
#include "GraphicsDevice.h"

namespace JFL
{
    namespace Direct3D12
    {
        class CommandList final : public JFCommandList
        {
        public:
            CommandList(ID3D12CommandAllocator*, ID3D12CommandList*, D3D12_COMMAND_LIST_TYPE);
            ~CommandList() noexcept = default;

            void Reset();

        private:
            D3D12_COMMAND_LIST_TYPE type;
            ComPtr<ID3D12CommandList> list;
            ComPtr<ID3D12CommandAllocator> allocator;
        };
    }
}
