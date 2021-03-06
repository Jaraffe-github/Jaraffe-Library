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
#include "Texture.h"

namespace JFL
{
	class JFWindow;

	namespace Private::Direct3D12
	{
		class CommandQueue;

		class SwapChain final : public JFSwapChain
		{
		public:
			SwapChain(GraphicsDevice*, CommandQueue*, const JFWindow*);
			~SwapChain() noexcept = default;

			uint32_t Width() override { return width; }
			uint32_t Height() override { return height; }

			const JFTexture* CurrentColorTexture() const override;
			const JFTexture* DepthStencilTexture() const override;

			void Resize(uint32_t width, uint32_t height) override;
			void Present() override;

		private:
			void SetupColorTextures();
			void SetupDepthStencil();

			uint32_t width;
			uint32_t height;

			UINT currentColorTextureIndex;
			mutable JFObject<Texture> colorTexture[FRAME_BUFFER_COUNT];
			mutable JFObject<Texture> depthStencilTexture;

			ComPtr<IDXGISwapChain3> swapChain;

			JFObject<GraphicsDevice> device;
		};
	}
}
