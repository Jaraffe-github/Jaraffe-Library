//
//  File: GraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGraphicsDevice.h"
#include "vulkan_headers.h"

namespace JFL::Vulkan
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

		void SetupDebugMessenger();
		
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
#if defined(DEBUG) || defined(_DEBUG)
		VkDebugUtilsMessengerEXT debugMessenger;
#endif
	};
}