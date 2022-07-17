//
//  File: GraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGraphicsDevice.h"
#include "d3d12_headers.h"
#include "CommandAllocator.h"
#include "Lock/JFLock.h"

namespace JFL::Private::Direct3D12
{
	class GraphicsDevice final : public JFGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept = default;

		JFObject<JFCommandQueue> CreateCommandQueue() override;
		JFObject<JFRenderPipeline> CreateRenderPipeline(const JFRenderPipelineDescriptor&) override;

		JFObject<JFGPUBuffer> CreateGPUBuffer(size_t, JFGPUBuffer::CPUCacheMode) override;
		JFObject<JFTexture> CreateTexture(const JFTextureDescriptor&) override;

		JFObject<JFShader> CreateShader(const JFArray<uint8_t>& code, const JFStringA& entry, JFShader::StageType stage) override;

		ComPtr<ID3D12GraphicsCommandList> GetCommandList(D3D12_COMMAND_LIST_TYPE type);
		JFObject<CommandAllocator> GetCommandAllocator(D3D12_COMMAND_LIST_TYPE type);
		void ReleaseCommandList(ID3D12GraphicsCommandList* list);
		void ReleaseCommandAllocator(CommandAllocator* allocator);

		ID3D12Device* Device() const { return device.Get(); }
		ComPtr<IDXGIFactory6> Factory() const { return factory; }

	private:
		JFSpinLock reusableListLock;
		JFArray<JFObject<CommandAllocator>> reusableAllocatorList;
		JFArray<ComPtr<ID3D12GraphicsCommandList>> reusableCommandList;
		ComPtr<ID3D12CommandAllocator> dummyAllocator;

		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory6> factory;

		D3D12_FEATURE_DATA_D3D12_OPTIONS d3d12Options;
		D3D12_FEATURE_DATA_ARCHITECTURE architecture;
	};
}
