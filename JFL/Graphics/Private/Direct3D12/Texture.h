//
//  File: Texture.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFTexture.h"
#include "d3d12_headers.h"

namespace JFL::Private::Direct3D12
{
	class Texture final : public JFTexture
	{
	public:
		Texture(ID3D12Resource*, D3D12_RESOURCE_STATES);
		~Texture() noexcept = default;

		size_t Size() const;
		uint32_t Width() const { return width; }
		uint32_t Height() const { return height; }
		JFPixelFormat Format() const { return format; }

		ID3D12Resource* Resource() const { return resource.Get(); }
		D3D12_RESOURCE_STATES InitialState() const { return initialState; }

		void SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap);
		void SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap);
		void SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap);

		D3D12_CPU_DESCRIPTOR_HANDLE ShaderResourceView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

	private:
		uint32_t width;
		uint32_t height;
		JFPixelFormat format;
		D3D12_RESOURCE_STATES initialState;

		ComPtr<ID3D12Resource> resource;
		ComPtr<ID3D12DescriptorHeap> renderTargetViewHeap;
		ComPtr<ID3D12DescriptorHeap> depthStencilViewHeap;
		ComPtr<ID3D12DescriptorHeap> shaderResourceViewHeap;
	};
}
