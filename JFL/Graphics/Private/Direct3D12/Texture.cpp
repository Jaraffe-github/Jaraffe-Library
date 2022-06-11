//
//  File: Texture.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "Texture.h"
#include "Types.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

Texture::Texture(ID3D12Resource* resource, D3D12_RESOURCE_STATES initialState)
	: resource(resource)
	, initialState(initialState)
{
	D3D12_RESOURCE_DESC desc = resource->GetDesc();
	width = static_cast<uint32_t>(desc.Width);
	height = static_cast<uint32_t>(desc.Height);
	format = PixelFormat(desc.Format);
}

size_t Texture::Size() const
{
	return AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
}

void Texture::SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap)
{
	renderTargetViewHeap = heap;
}

void Texture::SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap)
{
	depthStencilViewHeap = heap;
}

void Texture::SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap)
{
	shaderResourceViewHeap = heap;
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::ShaderResourceView() const
{
	JFASSERT(shaderResourceViewHeap);
	return shaderResourceViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::RenderTargetView() const
{
	JFASSERT(renderTargetViewHeap);
	return renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::DepthStencilView() const
{
	JFASSERT(depthStencilViewHeap);
	return depthStencilViewHeap->GetCPUDescriptorHandleForHeapStart();
}
