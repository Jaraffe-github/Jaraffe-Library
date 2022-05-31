//
//  File: JFTexture.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFRefCounter.h"
#include "JFPixelFormat.h"

namespace JFL
{
	class JFL_API JFTexture : public JFRefCounter
	{
	public:
		enum Type
		{
			Type1D,
			Type2D,
			Type3D,
		};
		enum Usage : uint32_t
		{
			UsageNone = 0U,
			UsageShaderRead = 1U,
			UsageRenderTarget = 1U << 1,
			UsageDepthStencil = 1U << 2,
		}; 
		
		JFTexture() = default;
		virtual ~JFTexture() noexcept = default;

		virtual size_t Size() const = 0;
		virtual uint32_t Width() const = 0;
		virtual uint32_t Height() const = 0;
		virtual JFPixelFormat Format() const = 0;
	};

	struct JFTextureDescriptor
	{
		JFTexture::Type type;
		JFPixelFormat format;
		uint32_t width;
		uint32_t height;
		uint32_t depth;
		uint32_t mipmapLevelCount;
		uint32_t sampleCount;
		uint32_t usage;
	};
}