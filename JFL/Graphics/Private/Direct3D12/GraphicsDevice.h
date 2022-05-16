//
//  File: GraphicsDevice.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGraphicsDevice.h"
#include "d3d12_headers.h"

namespace JFL
{
	class GraphicsDevice : public JFGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept = default;

		ID3D12Device* Device() const { return device.Get(); }
		ComPtr<IDXGIFactory6> Factory() const { return factory; }

	private:
		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory6> factory;

		D3D12_FEATURE_DATA_D3D12_OPTIONS d3d12Options;
		D3D12_FEATURE_DATA_ARCHITECTURE architecture;
	};
}
