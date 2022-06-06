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

		ID3D12Resource* Buffer() const { return buffer.Get(); }
		D3D12_RESOURCE_STATES InitialState() const { return initialState; }

	private:
		uint32_t width;
		uint32_t height;
		JFPixelFormat format;

		ComPtr<ID3D12Resource> buffer;
		D3D12_RESOURCE_STATES initialState;
	};
}
