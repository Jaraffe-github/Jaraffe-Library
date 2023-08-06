//
//  File: GraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGraphicsDevice.h"
#include "VulkanHeaders.h"
#include "QueueFamily.h"

namespace JFL::Private::Vulkan
{
	class GraphicsDevice final : public JFGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept;

		JFObject<JFCommandQueue> CreateCommandQueue() override;
		JFObject<JFRenderPipeline> CreateRenderPipeline(const JFRenderPipelineDescriptor&) override;

		JFObject<JFGPUBuffer> CreateGPUBuffer(const JFGPUBufferDescriptor& descriptor) override;
		JFObject<JFTexture> CreateTexture(const JFTextureDescriptor&) override;

		JFObject<JFShader> CreateShader(const JFArray<uint8_t>& path, const JFStringA& entry, JFShader::StageType stage) override;

		VkInstance Instance() const { return instance; }
		VkDevice Device() const { return device; }
		VkPhysicalDevice PhysicalDevice() const { return physicalDevice; }

	private:
		bool CheckValidationLayersSupport(const JFArray<const char*>& validationLayers) const;
		bool CheckInstanceExtensionsSupport(const JFArray<const char*>& extensions) const;
		bool CheckDeviceExtensionsSupport(VkPhysicalDevice physicalDevice, const JFArray<const char*>& extensions) const;

		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;

		JFArray<JFObject<QueueFamily>> queueFamilies;
	};
}