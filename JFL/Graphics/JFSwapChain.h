//
//  File: JFSwapChain.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"

namespace JFL
{
	class JFWindow;
	class JFTexture;

	// TODO: Similar ref: https://developer.apple.com/documentation/metalkit/mtkview
	class JFL_API JFSwapChain : public JFRefCounter
	{
	public:
		enum { FRAME_BUFFER_COUNT = 2 };

		JFSwapChain() = default;
		virtual ~JFSwapChain() noexcept = default;

		virtual uint32_t Width() = 0;
		virtual uint32_t Height() = 0;

		virtual const JFTexture* CurrentColorTexture() const = 0;
		virtual const JFTexture* DepthStencilTexture() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual void Present() = 0;
	};
}
