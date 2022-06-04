//
//  File: SwapChain.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFSwapChain.h"
#include "d3d12_headers.h"
#include "Object/JFObject.h"
#include "GraphicsDevice.h"

namespace JFL
{
	class JFWindow;

	namespace Direct3D12
	{
		class CommandQueue;

		class SwapChain final : public JFSwapChain
		{
		public:
			SwapChain(GraphicsDevice*, CommandQueue*, const JFWindow*);
			~SwapChain() noexcept = default;

			uint32_t Width() override { return width; }
			uint32_t Height() override { return height; }

			void Resize(uint32_t width, uint32_t height) override;

		private:
			uint32_t width;
			uint32_t height;

			UINT currentColorTextureIndex;
			mutable ComPtr<ID3D12Resource> colorTexture[FRAME_BUFFER_COUNT];
			mutable ComPtr<ID3D12Resource> depthStencilTexture;

			ComPtr<IDXGISwapChain3> swapChain;

			JFObject<GraphicsDevice> device;
		};
	}
}
