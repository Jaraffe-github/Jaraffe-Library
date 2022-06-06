//
//  File: GraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGraphicsDevice.h"
#include "vulkan_headers.h"
#include "QueueFamily.h"
#include <vector>

namespace JFL::Private::Vulkan
{
	class GraphicsDevice final : public JFGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept;

		JFObject<JFCommandQueue> CreateCommandQueue() override;
		JFObject<JFCommandList> CreateCommandList() override;

		JFObject<JFGPUBuffer> CreateGPUBuffer(size_t, JFGPUBuffer::CPUCacheMode) override;
		JFObject<JFTexture> CreateTexture(const JFTextureDescriptor&) override;

	private:
		bool CheckValidationLayersSupport(const std::vector<const char*>& validationLayers) const;
		bool CheckExtensionsSupport(const std::vector<const char*>& extensions) const;

		VkInstance instance;
		VkDevice device;

		std::vector<QueueFamily> queueFamilies;
	};
}