//
//  File: Shader.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Shader.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

Shader::Shader(GraphicsDevice* device, VkShaderModule shaderModule, StageType stage, const JFStringA& entry)
	: device(device)
	, shaderModule(shaderModule)
	, stage(stage)
	, entryName(entry)
{
}

Shader::~Shader()
{
	JFASSERT_DEBUG(device);
	vkDestroyShaderModule(device->Device(), shaderModule, nullptr);
}

VkPipelineShaderStageCreateInfo Shader::PipelineShaderStageInfo() const
{
	VkPipelineShaderStageCreateInfo shaderStageInfo{};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.module = shaderModule;
	shaderStageInfo.pName = entryName;

	switch (stage)
	{
	case StageType::Vertex:
		shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case StageType::Fragment:
		shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	}
	
	return shaderStageInfo;
}
