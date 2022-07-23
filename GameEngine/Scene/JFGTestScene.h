//
//  File: JFGTestScene.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFL.h"
#include "JFGInclude.h"
#include "Light/JFGLight.h"
#include "Model/JFGModel.h"

namespace JFG
{
	enum { MaxLights = 16 };

	struct JFGObjectConstants
	{
		JFMatrix4 world;
		JFMatrix4 texTransform;
	};

	struct JFGMainPassConstants
	{
		JFMatrix4 view;
		JFMatrix4 invView;
		JFMatrix4 proj;
		JFMatrix4 invProj;
		JFMatrix4 viewProj;
		JFMatrix4 invViewProj;
		JFVector3 eyePosW;
		float cbPerObjectPad1 = 0.0f;
		JFVector2 renderTargetSize;
		JFVector2 invRenderTargetSize;
		float nearZ;
		float farZ;
		JFVector2 pad2;
		JFLinearColor ambientLight = { 0.f, 0.f, 0.f, 1.f };

		JFGLight lights[MaxLights];
	};

	struct JFGMaterialConstants
	{
		JFLinearColor diffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		JFVector3 fresnelR0 = { 0.01f, 0.01f, 0.01f };
		float roughness = 0.25f;

		// Used in texture mapping.
		JFMatrix4 matTransform = {};
	};

	class JFGTestScene final : public JFRefCounter
	{
	public:
		JFGTestScene();
		~JFGTestScene();

		void Initialize();
		void Terminate();
		void Update();
		void Render();

	protected:
		void OnWindowEvent(const JFWindowEvent& windowEvent);

	private:
		void CreateWhiteTexture();
		void BuildConstantsBuffers();
		void BuildRenderPipeline();

		void UpdateCamera();
		void UpdateMainPassConstants();
		void UpdateObjectConstants(const JFGModel& renderItem);
		void UpdateMaterialConstants(const JFGModel& renderItem);

		JFGModel LoadModel(const JFStringA& path);

		JFCamera camera;
		JFArray<JFGModel> models;

		JFObject<JFRenderPipeline> renderPipeline;
		JFObject<JFGPUBuffer> mainPassConstantsBuffer;
		JFObject<JFGPUBuffer> objectConstantsBuffer;
		JFObject<JFGPUBuffer> materialConstantsBuffer;

	private:
		JFObject<JFWindow> window;
		JFObject<JFSwapChain> swapChain;

		JFObject<JFCommandQueue> commandQueue;
		JFObject<JFGraphicsDevice> graphicsDevice;
		
		JFObject<JFTexture> whiteTexture;

		std::atomic_bool resized;
	};
}
