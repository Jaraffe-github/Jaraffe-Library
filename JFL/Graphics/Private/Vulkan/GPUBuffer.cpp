//
//  File: GPUBuffer.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2023 Seungmin Choi. All rights reserved.
//

#include "GPUBuffer.h"
#include "VulkanUtils.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

GPUBuffer::GPUBuffer(GraphicsDevice* device, VkBuffer vkBuffer, VkDeviceMemory vkMemory, const JFGPUBufferDescriptor& descriptor)
	: device(device)
	, vkBuffer(vkBuffer)
	, vkMemory(vkMemory)
	, descriptor(descriptor)
{
}

GPUBuffer::~GPUBuffer() noexcept
{
	vkDestroyBuffer(device->Device(), vkBuffer, nullptr);
	vkFreeMemory(device->Device(), vkMemory, nullptr);
}

bool GPUBuffer::WriteData(const void* data, size_t size)
{
	if (descriptor.memoryLocation == GPUBuffer::MemoryLocation::CPUAndGPU)
	{
		void* mappedGPUData = nullptr;
		if (VkResult result = vkMapMemory(device->Device(), vkMemory, 0, size, 0, &mappedGPUData); result == VK_SUCCESS)
		{
			memcpy(mappedGPUData, data, size);

			vkUnmapMemory(device->Device(), vkMemory);

			return true;
		}
		else
		{
			JFLogWarning("Failed to vkMapMemory during the WriteData function call. ErrorMsg:{}", Tool::ErrorString(result));
		}
	}
	else
	{
		JFLogWarning("Failed to write data because it's GPU only.");
	}

	return false;
}

bool GPUBuffer::WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize)
{
	return false;
}

bool GPUBuffer::ReadData(void* data, size_t size)
{
	if (descriptor.memoryLocation == GPUBuffer::MemoryLocation::CPUAndGPU)
	{
		void* mappedGPUData = nullptr;
		if (VkResult result = vkMapMemory(device->Device(), vkMemory, 0, size, 0, &mappedGPUData); result == VK_SUCCESS)
		{
			memcpy(data, mappedGPUData, size);

			vkUnmapMemory(device->Device(), vkMemory);

			return true;
		}
		else
		{
			JFLogWarning("Failed to vkMapMemory during the ReadData function call. ErrorMsg:{}", Tool::ErrorString(result));
		}
	}
	else
	{
		JFLogWarning("Failed to read data because it's GPU only.");
	}

	return false;
}

bool GPUBuffer::SyncHostToDevice(size_t offset, size_t size)
{
	if (descriptor.cacheMode != JFGPUBuffer::CPUCacheMode::Synchronized)
	{
		if (offset < descriptor.size)
		{
			VkMappedMemoryRange memoryRange = {};
			memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			memoryRange.memory = vkMemory;
			memoryRange.offset = offset;
			memoryRange.size = JFNumeric::Min(size, descriptor.size);
			vkFlushMappedMemoryRanges(device->Device(), 1, &memoryRange);
			return true;
		}
		else
		{
			JFLogWarning("Offset exceeded the buffer size during the SyncHostToDevice function call.");
		}
	}
	else
	{
		return true;
	}
	
	return false;
}

bool GPUBuffer::SyncDeviceToHost(size_t offset, size_t size)
{
	if (descriptor.cacheMode != JFGPUBuffer::CPUCacheMode::Synchronized)
	{
		if (offset < descriptor.size)
		{
			VkMappedMemoryRange memoryRange = {};
			memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			memoryRange.memory = vkMemory;
			memoryRange.offset = offset;
			memoryRange.size = JFNumeric::Min(size, descriptor.size);
			vkInvalidateMappedMemoryRanges(device->Device(), 1, &memoryRange);
		}
		else
		{
			JFLogWarning("Offset exceeded the buffer size during the SyncDeviceToHost function call.");
		}
	}
	else
	{
		return true;
	}

	return false;
}