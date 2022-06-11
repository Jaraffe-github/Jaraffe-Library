//
//  File: RenderCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFRenderCommandEncoder.h"
#include "d3d12_headers.h"
#include "CommandBuffer.h"

namespace JFL::Private::Direct3D12
{
	class RenderCommandEncoder : public JFRenderCommandEncoder
	{
	public:
		RenderCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
		~RenderCommandEncoder() = default;

		 void SetViewport(const JFViewport& viewport) override;
		 void SetViewports(const JFViewport* viewports, uint32_t count) override;
		 void SetScissorRect(const JFRect& rect) override;
		 void SetScissorRects(const JFRect* rects, uint32_t count) override;

		 void SetRenderTargets(std::vector<const JFTexture*> renderTargets, const JFTexture* depthStencil) override;

		 void ClearRenderTargetView(const JFTexture* renderTarget, const JFLinearColor& clearColor) override;
		 void ClearDepthStencilView(const JFTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;
		
		 void EndEncoding() override;

	private:
		void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

		JFObject<CommandBuffer> commandBuffer;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}