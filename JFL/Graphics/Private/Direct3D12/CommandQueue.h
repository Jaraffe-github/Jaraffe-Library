//
//  File: CommandQueue.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFCommandQueue.h"
#include "d3d12_headers.h"
#include "GraphicsDevice.h"
#include "Lock/JFLock.h"

namespace JFL::Private::Direct3D12
{
	class GraphicsDevice;

	class CommandQueue final : public JFCommandQueue
	{
	public:
		CommandQueue(GraphicsDevice*, ID3D12CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, ID3D12Fence*);
		~CommandQueue() noexcept = default;

		JFObject<JFSwapChain> CreateSwapChain(const JFWindow*) override;
		JFObject<JFCommandBuffer> CreateCommandBuffer() override;

		void WaitComplete() override;

		ID3D12CommandQueue* Queue() const { return queue.Get(); }

		uint64_t ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists);

	private:
		JFSpinLock lock;
		UINT64 currentFenceNumber;
		ComPtr<ID3D12Fence> fence;
		ComPtr<ID3D12CommandQueue> queue;
		JFObject<GraphicsDevice> device;

		ComPtr<ID3D12CommandAllocator> commandAllocator;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}
