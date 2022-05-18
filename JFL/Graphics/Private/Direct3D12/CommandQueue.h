//
//  File: CommandQueue.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandQueue.h"
#include "d3d12_headers.h"
#include "GraphicsDevice.h"

namespace JFL
{
    class GraphicsDevice;

	class JFL_API CommandQueue final : public JFCommandQueue
	{
	public:
        CommandQueue(GraphicsDevice*, ID3D12CommandQueue*);
        ~CommandQueue() noexcept = default;

        JFObject<JFSwapChain> CreateSwapChain(const JFWindow*) override;

        ID3D12CommandQueue* Queue() const { return queue.Get(); }

    private:
        ComPtr<ID3D12CommandQueue> queue;
        JFObject<GraphicsDevice> device;
	};
}