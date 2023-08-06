//
//  File: JFGPUBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFRefCounter.h"

namespace JFL
{
	class JFL_API JFGPUBuffer : public JFRefCounter
	{
	public:
		enum { WHOLE_SIZE = ~0ULL };

		enum Usage : uint8_t
		{
			UsageIndexBuffer	= 0,
			UsageVertexBuffer	= 1 << 0,
		};

		enum class MemoryLocation
		{
			GPUOnly = 0,      // The resource can be accessed only by the GPU.
			CPUAndGPU         // The resource can be accessed by both the CPU and GPU.
		};

		enum class CPUCacheMode
		{
			None = 0,           // The resource is primarily accessed by the GPU. CPU access is not optimized and may require explicit synchronization.
			WriteCombined,      // Optimized for CPU writes. CPU writes to the resource may bypass caches, requiring synchronization before GPU access. Not optimized for CPU reads.
			ReadCombined,       // Optimized for CPU reads. Reading from the resource on the CPU may utilize caches, requiring synchronization before GPU modifications. Not optimized for CPU writes.
			Synchronized,       // Memory changes from the CPU are automatically visible to the GPU and vice-versa. Simplifies synchronization, but might affect performance.
		};

		enum class SharingMode
		{
			// Supports using the image or buffer by a single queue exclusively.
			// Direct transfer to another queue is not allowed, and a transition is needed
			// to make it usable by another queue.
			Exclusive = 0, 

			// Supports using the image or buffer by multiple queues concurrently.
			// It allows direct sharing between queues without requiring a transition.
			Concurrent,
		};

		JFGPUBuffer() = default;
		virtual ~JFGPUBuffer() noexcept = default;

		virtual size_t Size() const = 0;

		// Must be memory location is CPUAndGPU.
		virtual bool WriteData(const void* data, size_t size) = 0;
		virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) = 0;
		virtual bool ReadData(void* data, size_t size) = 0;

		// Synchronize manually.
		virtual bool SyncHostToDevice(size_t offset = 0, size_t size = WHOLE_SIZE) = 0;
		virtual bool SyncDeviceToHost(size_t offset = 0, size_t size = WHOLE_SIZE) = 0;
	};

	struct JFGPUBufferDescriptor
	{
		size_t size;
		JFGPUBuffer::Usage usage;
		JFGPUBuffer::MemoryLocation memoryLocation;
		JFGPUBuffer::CPUCacheMode cacheMode;
		JFGPUBuffer::SharingMode sharingMode;
	};
}