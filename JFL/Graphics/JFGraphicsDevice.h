//
//  File: JFGraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "JFCommandQueue.h"
#include "JFCommandList.h"
#include "JFGPUBuffer.h"
#include "JFTexture.h"

namespace JFL
{
	class JFL_API JFGraphicsDevice : public JFRefCounter
	{
	public:
		virtual ~JFGraphicsDevice() noexcept = default;

		static JFGraphicsDevice* CreateGraphicsDevice();

		virtual JFObject<JFCommandQueue> CreateCommandQueue() = 0;
		virtual JFObject<JFCommandList> CreateCommandList() = 0;

		virtual JFObject<JFGPUBuffer> CreateGPUBuffer(size_t size, JFGPUBuffer::CPUCacheMode mode) = 0;
		virtual JFObject<JFTexture> CreateTexture(const JFTextureDescriptor& descriptor) = 0;

	protected:
		JFGraphicsDevice() = default;
	};
}
