//
//  File: JFRenderPipeline.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "JFShader.h"
#include "JFVertexDescriptor.h"
#include "JFPixelFormat.h"
#include "JFBlendState.h"

namespace JFL
{
	class JFL_API JFRenderPipeline : public JFRefCounter
	{
	public:
		JFRenderPipeline() = default;
		virtual ~JFRenderPipeline() noexcept = default;
	};

	enum class JFPrimitiveTopologyType
	{
		Point,
		Line,
		Triangle
	};

	struct JFRenderPipelineColorAttachmentDescriptor
	{
		JFPixelFormat pixelFormat;

		bool blendingEnabled;

		JFBlendOperation alphaBlendOperation;
		JFBlendFactor sourceAlphaBlendFactor;
		JFBlendFactor destinationAlphaBlendFactor;

		JFBlendOperation rgbBlendOperation;
		JFBlendFactor sourceRGBBlendFactor;
		JFBlendFactor destinationRGBBlendFactor;

		JFColorWriteMask writeMask = JFColorWriteMask::ColorWriteMaskAll;
	};

	// TODO: ref https://developer.apple.com/documentation/metal/mtlrenderpipelinedescriptor
	struct JFRenderPipelineDescriptor
	{
		uint32_t sampleCount;
		JFObject<JFShader> vertexShader;
		JFObject<JFShader> fragmentShader;

		JFVertexDescriptor vertexDescriptor;
		JFArray<JFRenderPipelineColorAttachmentDescriptor> colorAttachments;
		JFPixelFormat depthStencilAttachmentPixelFormat;

		JFPrimitiveTopologyType inputPrimitiveTopology;
	};
}
