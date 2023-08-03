//
//  File: Texture.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Texture.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

Texture::Texture(GraphicsDevice* device, VkImage image, VkImageView imageView, VkFramebuffer frameBuffer)
	: image(image)
	, imageView(imageView)
	, frameBuffer(frameBuffer)
	, device(device)
	, width(0)
	, height(0)
	, format()
{
}

Texture::Texture(const Texture& texture)
	: image(texture.image)
	, imageView(texture.imageView)
	, frameBuffer(texture.frameBuffer)
	, device(texture.device)
	, width(texture.width)
	, height(texture.height)
	, format(texture.format)
{
}

Texture::~Texture() noexcept
{
	vkDestroyFramebuffer(device->Device(), frameBuffer, nullptr);
	vkDestroyImageView(device->Device(), imageView, nullptr);
	//vkDestroyImage(device->Device(), image, nullptr);
}

size_t Texture::Size() const
{
	return 0;
}