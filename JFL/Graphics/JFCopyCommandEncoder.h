//
//  File: JFCopyCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"

namespace JFL
{
    class JFTexture;
    class JFGPUBuffer;

	class JFL_API JFCopyCommandEncoder : public JFRefCounter
	{
	public:
		struct TextureArea
		{
			uint32_t x, y;
			uint32_t width, height;
		};

		JFCopyCommandEncoder() = default;
		virtual ~JFCopyCommandEncoder() noexcept = default;

		virtual void CopyBufferToBuffer(JFGPUBuffer* src, size_t srcOffset, JFGPUBuffer* dest, size_t destOffset, size_t copySize) = 0;
		virtual void CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea) = 0;
		virtual void CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset) = 0;

		virtual void EndEncoding() = 0;
	};
}