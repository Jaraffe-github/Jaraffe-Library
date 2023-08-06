//
//  File: GPUBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFGPUBuffer.h"
#include "VulkanHeaders.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Vulkan
{
	class GPUBuffer final : public JFGPUBuffer
	{
	public:
		GPUBuffer(GraphicsDevice* device, VkBuffer vkBuffer, VkDeviceMemory vkMemory, const JFGPUBufferDescriptor& descriptor);
		~GPUBuffer() noexcept;

		size_t Size() const override { return descriptor.size; }

		bool WriteData(const void* data, size_t size) override;
		bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) override;
		bool ReadData(void* data, size_t size) override;

		bool SyncHostToDevice(size_t offset, size_t size) override;
		bool SyncDeviceToHost(size_t offset, size_t size) override;

		VkBuffer Buffer() const { return vkBuffer; }
		VkDeviceMemory Memory() const { return vkMemory; }
		const JFGPUBufferDescriptor& Descriptor() const { return descriptor; }

	private:
		JFObject<GraphicsDevice> device;
		JFGPUBufferDescriptor descriptor;

		VkBuffer vkBuffer;
		VkDeviceMemory vkMemory;
	};
}
