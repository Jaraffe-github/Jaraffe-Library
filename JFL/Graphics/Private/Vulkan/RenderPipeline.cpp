//
//  File: RenderPipeline.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "RenderPipeline.h"
#include "GraphicsDevice.h"

using namespace JFL;
using namespace JFL::Private::Vulkan;

RenderPipeline::RenderPipeline(GraphicsDevice* device, VkPipeline pipeline, VkRenderPass renderPass, VkPipelineLayout pipelineLayout)
	: device(device)
	, pipeline(pipeline)
	, renderPass(renderPass)
	, pipelineLayout(pipelineLayout)
{
}

RenderPipeline::~RenderPipeline()
{
	JFASSERT_DEBUG(device);
	vkDestroyPipeline(device->Device(), pipeline, nullptr);
	vkDestroyPipelineLayout(device->Device(), pipelineLayout, nullptr);
	vkDestroyRenderPass(device->Device(), renderPass, nullptr);
}
