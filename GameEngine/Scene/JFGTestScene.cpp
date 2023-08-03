//
//  File: JFGTestScene.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFGTestScene.h"
#include "tiny_obj_loader.h"

using namespace JFG;

JFGTestScene::JFGTestScene()
	: resized(true)
{
}

JFGTestScene::~JFGTestScene()
{
}

void JFGTestScene::Initialize()
{
	JFWindowDescriptor windowDescriptor{};
	windowDescriptor.title = L"Jaraffe Game Engine";
	window = JFWindow::CreatePlatformWindow();
	window->Create(windowDescriptor);
	window->Show();

	window->AddWindowEventListener(this, std::bind(&JFGTestScene::OnWindowEvent, this, std::placeholders::_1));

	graphicsDevice = JFGraphicsDevice::CreateGraphicsDevice(JFL::JFGraphicsType::Vulkan);
	commandQueue = graphicsDevice->CreateCommandQueue();
	swapChain = commandQueue->CreateSwapChain(window);

	CreateWhiteTexture();

	BuildConstantsBuffers();
	BuildRenderPipeline();

	// models.Add(LoadModel("Resource/Meshes/bunny.obj"));
}

void JFGTestScene::Terminate()
{
	if (window)
		window->RemoveWindowEventListener(this);
}

void JFGTestScene::Update()
{
	if (resized)
	{
		camera.SetPerspective(0.25f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);
		swapChain->Resize(window->Width(), window->Height());
		resized = false;
	}

	UpdateCamera();
	//UpdateMainPassConstants();
}

void JFGTestScene::Render()
{
	if (JFObject<JFCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
	{
		if (JFObject<JFRenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
		{
			JFViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
			encoder->SetViewport(viewport);

			JFRect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
			encoder->SetScissorRect(scissorRect);

			encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), JFLinearColor::black);
			encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), JFRenderCommandEncoder::DepthStencilClearFlag::All, 0.f, 0);

			encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

			// encoder->SetConstantBuffer(2, mainPassConstantsBuffer);

			//for (const JFGModel& model : models)
			//{
			//	UpdateObjectConstants(model);
			//	UpdateMaterialConstants(model);
			//
			//	encoder->SetConstantBuffer(0, objectConstantsBuffer);
			//	encoder->SetConstantBuffer(1, materialConstantsBuffer);
			//
			//	for (const JFGMesh& mesh : model.meshes)
			//	{
			//		encoder->SetVertexBuffer(mesh.vertexBuffer, sizeof(JFGVertex));
			//		encoder->DrawPrimitives(JFRenderCommandEncoder::PrimitiveType::Triangle,
			//								(uint32_t)mesh.vertices.Count(), 1, 0, 0);
			//	}
			//}

			encoder->DrawPrimitives(JFRenderCommandEncoder::PrimitiveType::Triangle, 3, 1, 0, 0);

			encoder->EndEncoding();
		}

		commandBuffer->Commit();
	}

	commandQueue->WaitComplete();

	// swap the back and front buffers.
	swapChain->Present();
}

void JFGTestScene::OnWindowEvent(const JFWindowEvent& windowEvent)
{
	switch (windowEvent.type)
	{
	case JFWindowEvent::Type::Resize:
		if (windowEvent.width > 0 && windowEvent.height > 0)
			resized = true;
		break;
	}
}

void JFGTestScene::CreateWhiteTexture()
{
	JFTextureDescriptor whiteTextureDesc;
	whiteTextureDesc.type = JFTexture::Type2D;
	whiteTextureDesc.format = JFPixelFormat::RGBA8Unorm;
	whiteTextureDesc.width = 4; // texture minimum size.
	whiteTextureDesc.height = 4; // texture minimum size.
	whiteTextureDesc.depth = 1;
	whiteTextureDesc.mipmapLevelCount = 1;
	whiteTextureDesc.sampleCount = 1;
	whiteTextureDesc.usage = JFTexture::UsageShaderRead;
	whiteTexture = graphicsDevice->CreateTexture(whiteTextureDesc);
}

void JFGTestScene::BuildConstantsBuffers()
{
	mainPassConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(JFGMainPassConstants), JFGPUBuffer::CPUCacheMode::WriteCombined);
	objectConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(JFGObjectConstants), JFGPUBuffer::CPUCacheMode::WriteCombined);
	materialConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(JFGMaterialConstants), JFGPUBuffer::CPUCacheMode::WriteCombined);
}

void JFGTestScene::BuildRenderPipeline()
{
	JFRenderPipelineDescriptor descriptor;
	descriptor.sampleCount = 1;
	descriptor.vertexShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimpleVertexShader.spv", "main", JFShader::StageType::Vertex);
	descriptor.fragmentShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimplePixelShader.spv", "main", JFShader::StageType::Fragment);
	descriptor.vertexDescriptor.attributes = {
		{JFVertexFormat::Float3, "COLOR", 0, 0 },
		// {JFVertexFormat::Float3, "POSITION", 0, 0 },
		// {JFVertexFormat::Float3, "NORMAL", 0, 12 },
		//{JFVertexFormat::Float4, "COLOR", 0, 24 },
		//{JFVertexFormat::Float2, "TEXCOORD", 0, 40 }
	};
	descriptor.colorAttachments = {
		{ JFPixelFormat::RGBA8Unorm, false }
	};
	descriptor.depthStencilAttachmentPixelFormat = JFPixelFormat::Depth24UnormStencil8;
	descriptor.inputPrimitiveTopology = JFPrimitiveTopologyType::Triangle;

	renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);
}

void JFGTestScene::UpdateCamera()
{
	camera.SetupViewMatrix(JFVector3{ 0.f, 3.f, -5.f }, JFVector3{}, JFVector3{ 0.f, 1.f, 0.f });
}

void JFGTestScene::UpdateMainPassConstants()
{
	auto viewMat = camera.ViewMatrix();
	auto projectionMat = camera.ProjectionMatrix();

	// HLSL is column-major matrix.
	JFGMainPassConstants mainPassConstants;
	mainPassConstants.view = viewMat.TransposeMatrix();
	mainPassConstants.invView = viewMat.InverseMatrix().TransposeMatrix();
	mainPassConstants.proj = projectionMat.TransposeMatrix();
	mainPassConstants.invProj = projectionMat.InverseMatrix().TransposeMatrix();
	mainPassConstants.viewProj = (viewMat * projectionMat).TransposeMatrix();
	mainPassConstants.invViewProj = (viewMat * projectionMat).InverseMatrix().TransposeMatrix();

	mainPassConstants.eyePosW = camera.Position();
	mainPassConstants.renderTargetSize = JFVector2((float)window->Width(), (float)window->Height());
	mainPassConstants.invRenderTargetSize = JFVector2(1.f / window->Width(), 1.f / window->Height());
	mainPassConstants.nearZ = camera.NearZ();
	mainPassConstants.farZ = camera.FarZ();
	mainPassConstants.ambientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mainPassConstants.lights[0].direction = { 0.57735f, -0.57735f, 0.57735f };
	mainPassConstants.lights[0].strength = { 0.6f, 0.6f, 0.6f };
	mainPassConstants.lights[1].direction = { -0.57735f, -0.57735f, 0.57735f };
	mainPassConstants.lights[1].strength = { 0.3f, 0.3f, 0.3f };
	mainPassConstants.lights[2].direction = { 0.0f, -0.707f, -0.707f };
	mainPassConstants.lights[2].strength = { 0.15f, 0.15f, 0.15f };

	mainPassConstantsBuffer->WriteData(&mainPassConstants, sizeof(JFGMainPassConstants));
}

void JFGTestScene::UpdateObjectConstants(const JFGModel& model)
{
	JFGObjectConstants objConstants;
	objConstants.world = model.world.TransposeMatrix();
	objConstants.texTransform = model.texTransform.TransposeMatrix();

	objectConstantsBuffer->WriteData(&objConstants, sizeof(JFGObjectConstants));
}

void JFGTestScene::UpdateMaterialConstants(const JFGModel& model)
{
	JFGMaterialConstants matConstants;
	matConstants.diffuseAlbedo = model.material.diffuseAlbedo;
	matConstants.fresnelR0 = model.material.fresnelR0;
	matConstants.roughness = model.material.roughness;
	matConstants.matTransform = model.texTransform;

	materialConstantsBuffer->WriteData(&matConstants, sizeof(JFGMaterialConstants));
}

JFGModel JFGTestScene::LoadModel(const JFStringA& path)
{
	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile(std::string(path)))
	{
		if (!reader.Error().empty())
			JFLogError(reader.Error().c_str());
		JFASSERT(false);
	}

	if (!reader.Warning().empty())
	{
		JFLogWarning(reader.Warning().c_str());
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	JFGModel newModel{};
	newModel.material.diffuseAlbedo = JFLinearColor(1.f, 1.f, 1.f, 1.f);
	newModel.material.fresnelR0 = JFVector3(0.05f, 0.05f, 0.05f);
	newModel.material.roughness = 0.3f;

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); ++s)
	{
		JFArray<JFGVertex> vertices;
		vertices.Reserve(shapes[s].mesh.num_face_vertices.size() * 3);

		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
		{
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; ++v)
			{
				JFGVertex vertex{};

				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				// access to vertex
				vertex.pos = JFVector3(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
									   attrib.vertices[3 * size_t(idx.vertex_index) + 1],
									   attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					vertex.normal = JFVector3(attrib.normals[3 * size_t(idx.normal_index) + 0],
											  attrib.normals[3 * size_t(idx.normal_index) + 1],
											  attrib.normals[3 * size_t(idx.normal_index) + 2]);
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				/*if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
				}*/

				// Optional: vertex colors
				vertex.color = JFLinearColor(attrib.colors[3 * size_t(idx.vertex_index) + 0],
											 attrib.colors[3 * size_t(idx.vertex_index) + 1],
											 attrib.colors[3 * size_t(idx.vertex_index) + 2],
											 1.f);

				vertices.Add(vertex);
			}
			index_offset += fv;
		}

		JFObject<JFGPUBuffer> vertexBuffer = graphicsDevice->CreateGPUBuffer(vertices.Bytes(), JFGPUBuffer::CPUCacheMode::WriteCombined);
		vertexBuffer->WriteData(vertices.Data(), vertices.Bytes());

		newModel.meshes.EmplaceAdd(std::move(vertices), vertexBuffer);
	}

	return newModel;
}
