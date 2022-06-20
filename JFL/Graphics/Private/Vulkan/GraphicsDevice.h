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

		JFObject<JFGPUBuffer> CreateGPUBuffer(size_t, JFGPUBuffer::CPUCacheMode) override;
		JFObject<JFTexture> CreateTexture(const JFTextureDescriptor&) override;

		JFObject<JFShader> CreateShader(const JFArray<uint8_t>& path, const JFStringW& entry, JFShader::StageType stage) override;

		VkInstance Instance() const { return instance; }
		VkDevice Device() const { return device; }
		VkPhysicalDevice PhysicalDevice() const { return physicalDevice; }

	private:
		bool CheckValidationLayersSupport(const std::vector<const char*>& validationLayers) const;
		bool CheckInstanceExtensionsSupport(const std::vector<const char*>& extensions) const;
		bool CheckDeviceExtensionsSupport(VkPhysicalDevice physicalDevice, const std::vector<const char*>& extensions) const;

		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;

		std::vector<JFObject<QueueFamily>> queueFamilies;
	};
}