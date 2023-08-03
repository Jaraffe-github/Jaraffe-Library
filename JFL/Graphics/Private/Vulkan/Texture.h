//
//  File: Texture.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFTexture.h"
#include "vulkan_headers.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Vulkan
{
	class Texture final : public JFTexture
	{
	public:
		Texture(GraphicsDevice* device, VkImage image, VkImageView imageView, VkFramebuffer frameBuffer);
		Texture(const Texture& texture);
		~Texture() noexcept;

		size_t Size() const;
		uint32_t Width() const { return width; }
		uint32_t Height() const { return height; }
		JFPixelFormat Format() const { return format; }

		VkImageView ImageView() const { return imageView; }
		VkFramebuffer FrameBuffer() const { return frameBuffer; }

	private:
		uint32_t width;
		uint32_t height;
		JFPixelFormat format;

		VkImage image;
		VkImageView imageView;
		VkFramebuffer frameBuffer;
		JFObject<GraphicsDevice> device;
	};
}
