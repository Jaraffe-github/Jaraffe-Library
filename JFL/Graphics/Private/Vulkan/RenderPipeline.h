//
//  File: RenderPipeline.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFRenderPipeline.h"
#include "JFInclude.h"
#include "VulkanHeaders.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Vulkan
{
	class RenderPipeline final : public JFRenderPipeline
	{
	public:
		RenderPipeline(GraphicsDevice* device, VkPipeline pipeline, VkRenderPass renderPass, VkPipelineLayout pipelineLayout);
		~RenderPipeline();

		VkPipeline Pipeline() const { return pipeline; }
		VkRenderPass RenderPass() const { return renderPass; }

	private:
		VkPipeline pipeline;
		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;

		JFObject<GraphicsDevice> device;
	};
}