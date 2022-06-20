//
//  File: JFGraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "Container/JFArray.h"
#include "JFCommandQueue.h"
#include "JFGPUBuffer.h"
#include "JFTexture.h"
#include "JFShader.h"

namespace JFL
{
	enum class JFGraphicsType
	{
		Direct3D12,
		Vulkan
	};

	class JFL_API JFGraphicsDevice : public JFRefCounter
	{
	public:
		virtual ~JFGraphicsDevice() noexcept = default;

		static JFGraphicsDevice* CreateGraphicsDevice(JFGraphicsType type);

		virtual JFObject<JFCommandQueue> CreateCommandQueue() = 0;

		virtual JFObject<JFGPUBuffer> CreateGPUBuffer(size_t size, JFGPUBuffer::CPUCacheMode mode) = 0;
		virtual JFObject<JFTexture> CreateTexture(const JFTextureDescriptor& descriptor) = 0;

		// TODO: need SPIR-V
		virtual JFObject<JFShader> CreateShader(const JFStringW& path, const JFStringW& entry, JFShader::StageType stage);
		virtual JFObject<JFShader> CreateShader(const JFArray<uint8_t>& path, const JFStringW& entry, JFShader::StageType stage) = 0;

	protected:
		JFGraphicsDevice() = default;
	};
}
