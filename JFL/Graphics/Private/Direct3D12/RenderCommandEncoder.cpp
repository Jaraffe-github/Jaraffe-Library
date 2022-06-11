//
//  File: RenderCommandEncoder.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "RenderCommandEncoder.h"
#include "texture.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

RenderCommandEncoder::RenderCommandEncoder(CommandBuffer* commandBuffer, ID3D12GraphicsCommandList* commandList)
	: commandBuffer(commandBuffer)
	, commandList(commandList)
{
}

void RenderCommandEncoder::SetViewport(const JFViewport& viewport)
{	 
	D3D12_VIEWPORT vp
	{
		viewport.x, viewport.y,
		viewport.width, viewport.height,
		viewport.nearDepth, viewport.farDepth
	};
	commandList->RSSetViewports(1, &vp);
}	 
	 
void RenderCommandEncoder::SetViewports(const JFViewport* viewports, uint32_t count)
{	 
	std::vector<D3D12_VIEWPORT> vps(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		vps[i].TopLeftX = viewports[i].x;
		vps[i].TopLeftY = viewports[i].y;
		vps[i].Width = viewports[i].width;
		vps[i].Height = viewports[i].height;
		vps[i].MinDepth = viewports[i].nearDepth;
		vps[i].MaxDepth = viewports[i].farDepth;
	}
	commandList->RSSetViewports(count, vps.data());
}	 
	 
void RenderCommandEncoder::SetScissorRect(const JFRect& rect)
{	 
	D3D12_RECT rt
	{
	  static_cast<LONG>(rect.x),
	  static_cast<LONG>(rect.y),
	  static_cast<LONG>(rect.x + rect.width),
	  static_cast<LONG>(rect.y + rect.height)
	};
	commandList->RSSetScissorRects(1, &rt);
}	 
	 
void RenderCommandEncoder::SetScissorRects(const JFRect* rects, uint32_t count)
{	 
	std::vector<D3D12_RECT> rts(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		rts[i].left = static_cast<LONG>(rects[i].x);
		rts[i].top = static_cast<LONG>(rects[i].y);
		rts[i].right = static_cast<LONG>(rects[i].x + rects[i].width);
		rts[i].bottom = static_cast<LONG>(rects[i].y + rects[i].height);
	}
	commandList->RSSetScissorRects(count, rts.data());
}	 
	 
void RenderCommandEncoder::SetRenderTargets(std::vector<const JFTexture*> renderTargets, const JFTexture* depthStencil)
{	 
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> renderTargetHandles;
	renderTargetHandles.reserve(renderTargets.size());
	for (const JFTexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
		JFASSERT_DEBUG(rt);

		renderTargetHandles.push_back(rt->RenderTargetView());
		TransitionBufferState(rt->Resource(), rt->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	}

	JFASSERT_DEBUG(renderTargetHandles.size() > 0);

	if (const Texture* ds = dynamic_cast<const Texture*>(depthStencil))
	{
		D3D12_CPU_DESCRIPTOR_HANDLE dsView = ds->DepthStencilView();
		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
										true, &dsView);
	}
	else
	{
		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetHandles.size()), renderTargetHandles.data(),
										false, nullptr);
	}

	for (const JFTexture* renderTarget : renderTargets)
	{
		const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
		JFASSERT_DEBUG(rt);

		TransitionBufferState(rt->Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, rt->InitialState());
	}
}	 
	 
void RenderCommandEncoder::ClearRenderTargetView(const JFTexture* renderTarget, const JFLinearColor& clearColor)
{	 
	const Texture* rt = dynamic_cast<const Texture*>(renderTarget);
	JFASSERT_DEBUG(rt);

	TransitionBufferState(rt->Resource(), rt->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	commandList->ClearRenderTargetView(rt->RenderTargetView(), clearColor.value, 0, nullptr);
	TransitionBufferState(rt->Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, rt->InitialState());
}	 
	 
void RenderCommandEncoder::ClearDepthStencilView(const JFTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil)
{	 
	D3D12_CLEAR_FLAGS flag = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
	switch (clearFlag)
	{
	case DepthStencilClearFlag::Depth:
		flag = D3D12_CLEAR_FLAG_DEPTH;
		break;
	case DepthStencilClearFlag::Stencil:
		flag = D3D12_CLEAR_FLAG_STENCIL;
		break;
	}

	const Texture* ds = dynamic_cast<const Texture*>(depthStencil);
	JFASSERT_DEBUG(ds);

	commandList->ClearDepthStencilView(ds->DepthStencilView(), flag, clearDepth, clearStencil, 0, nullptr);
}	 
	 
void RenderCommandEncoder::EndEncoding()
{
	commandList->Close();
	commandBuffer->AddEncodedCommandList(commandList.Get());
	commandList = nullptr;
}

void RenderCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
	if (before != after)
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
		commandList->ResourceBarrier(1, &barrier);
	}
}
