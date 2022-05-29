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
		enum class CPUCacheMode
		{
			None = 0,		// The resource can be accessed only by the GPU.
			WriteCombined,	// the CPU writes into, but never reads.
			ReadCombined,	// the CPU reads into, but never write.
		};

		JFGPUBuffer() = default;
		virtual ~JFGPUBuffer() noexcept = default;

		virtual size_t Size() const = 0;
		virtual bool IsWritable() const = 0;
		virtual bool IsReadable() const = 0;

		// must be cache mode is WriteCombined.
		virtual bool WriteData(const void* data, size_t size) = 0;
		virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) = 0;
		// must be cache mode is ReadCombined.
		virtual bool ReadData(void* data, size_t size) = 0;
	};
}