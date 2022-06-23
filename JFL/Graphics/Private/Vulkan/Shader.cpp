//
//  File: Shader.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Shader.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

Shader::Shader(VkShaderModule shaderModule, StageType stage, const JFStringA& entry)
	: shaderModule(shaderModule)
	, stage(stage)
	, entryName(entry)
{
}
