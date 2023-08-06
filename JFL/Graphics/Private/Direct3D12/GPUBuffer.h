//
//  File: GPUBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGPUBuffer.h"
#include "d3d12_headers.h"
#include "GPUBuffer.h"

namespace JFL::Private::Direct3D12
{
	class GPUBuffer final : public JFGPUBuffer
	{
	public:
		GPUBuffer(ID3D12Resource*, CPUCacheMode, D3D12_RESOURCE_STATES);
		~GPUBuffer() noexcept = default;

		size_t Size() const override { return size; }
		bool IsWritable() const override { return writable; };
		bool IsReadable() const override { return readable; };

		bool WriteData(const void* data, size_t size) override;
		bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) override;
		bool ReadData(void* data, size_t size) override;

		ID3D12Resource* Buffer() const { return buffer.Get(); }
		D3D12_RESOURCE_STATES InitialState() const { return initialState; }

	private:
		size_t size;
		bool writable;
		bool readable;
		ComPtr<ID3D12Resource> buffer;
		D3D12_RESOURCE_STATES initialState;
	};
}