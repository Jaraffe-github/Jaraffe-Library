//
//  File: Shader.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFShader.h"
#include "JFInclude.h"
#include "vulkan_headers.h"
#include "Object/JFRefCounter.h"
#include "Container/JFContainer.h"

namespace JFL::Private::Vulkan
{
	class Shader final : public JFShader
	{
	public:
		Shader(VkShaderModule, StageType stage, const JFStringW& entry);
		~Shader() = default;

	private:
		VkShaderModule shaderModule;
		StageType stage;
		JFStringW entryName;
	};
}
