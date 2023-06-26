#include "gtest/gtest.h"
#include "JFL.h"
#include <thread>
// #include "tiny_obj_loader.h"

using namespace JFL;

struct Vertex
{
	JFVector3 pos;
	JFVector3 normal;
	JFLinearColor color;
};

struct StaticMesh
{
	JFArray<Vertex> vertices;
	JFObject<JFGPUBuffer> vertexBuffer;
};

struct Constants
{
	JFMatrix4 worldViewProj;
};

class TestApplication : public JFApplication
{
public:
	TestApplication()
		: window(nullptr)
		//, graphicsDevice(nullptr)
	{}

	void OnInitialize() override
	{
		JFWindowDescriptor windowDescriptor{};
		windowDescriptor.title = L"Jaraffe unit test window";
		window = JFWindow::CreatePlatformWindow();
		window->Create(windowDescriptor);
		window->Show();

//		graphicsDevice = JFGraphicsDevice::CreateGraphicsDevice(JFL::JFGraphicsType::Direct3D12);
//		commandQueue = graphicsDevice->CreateCommandQueue();
//		swapChain = commandQueue->CreateSwapChain(window);
//
//		JFTextureDescriptor whiteTextureDesc;
//		whiteTextureDesc.type = JFTexture::Type2D;
//		whiteTextureDesc.format = JFPixelFormat::RGBA8Unorm;
//		whiteTextureDesc.width = 4; // texture minimum size.
//		whiteTextureDesc.height = 4; // texture minimum size.
//		whiteTextureDesc.depth = 1;
//		whiteTextureDesc.mipmapLevelCount = 1;
//		whiteTextureDesc.sampleCount = 1;
//		whiteTextureDesc.usage = JFTexture::UsageShaderRead;
//		whiteTexture = graphicsDevice->CreateTexture(whiteTextureDesc);
//
//		vertexShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimpleShader.hlsl", "VS", JFShader::StageType::Vertex);
//		pixelShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimpleShader.hlsl", "PS", JFShader::StageType::Fragment);
//
//		JFRenderPipelineDescriptor descriptor{};
//		descriptor.sampleCount = 1;
//		descriptor.vertexShader = vertexShader;
//		descriptor.fragmentShader = pixelShader;
//		descriptor.vertexDescriptor.attributes = {
//			{JFVertexFormat::Float3, "POSITION", 0, 0},
//			{JFVertexFormat::Float3, "NORMAL", 0, 12 },
//			{JFVertexFormat::Float4, "COLOR", 0, 24 },
//		};
//		descriptor.colorAttachments = {{ JFPixelFormat::RGBA8Unorm, false }};
//		descriptor.depthStencilAttachmentPixelFormat = JFPixelFormat::Depth24UnormStencil8;
//		descriptor.inputPrimitiveTopology = JFPrimitiveTopologyType::Triangle;
//
//		renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);
//
//		camera.SetupViewMatrix(JFVector3{ 0.f, 0.f, -5.f }, JFVector3{}, JFVector3{ 0.f, 1.f, 0.f });
//		camera.SetPerspective(0.25f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);
//
//		Constants constants;
//		constants.worldViewProj = camera.ViewMatrix() * camera.ProjectionMatrix();
//
//		// Update the constant buffer with the latest worldViewProj matrix.
//		constantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(Constants), JFGPUBuffer::CPUCacheMode::WriteCombined);
//		constantsBuffer->WriteData(&constants, sizeof(Constants));
//
//		LoadTestModel();

//		loopThread = std::jthread([this](std::stop_token token)
//		{
//			while (!token.stop_requested())
//			{
//				Update();
//				Draw();
//			}
//		});
	}

	void OnTerminate() override
	{
//		loopThread.request_stop();
//		loopThread.join();
	}

	void Update()
	{

	}

	void Draw()
	{
//		if (JFObject<JFCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
//		{
//			if (JFObject<JFRenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
//			{
//				JFViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
//				encoder->SetViewport(viewport);
//
//				JFRect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
//				encoder->SetScissorRect(scissorRect);
//
//				encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), JFLinearColor::black);
//				encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), JFRenderCommandEncoder::DepthStencilClearFlag::All, 0.f, 0);
//
//				encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());
//
//				encoder->SetConstantBuffer(0, constantsBuffer);
//
//				for (const StaticMesh& mesh : staticMeshes)
//				{
//					encoder->SetVertexBuffer(mesh.vertexBuffer, sizeof(Vertex));
//
//					encoder->DrawPrimitives(JFRenderCommandEncoder::PrimitiveType::Triangle,
//											(uint32_t)mesh.vertices.Count(), 1, 0, 0);
//				}
//
//				encoder->EndEncoding();
//			}
//
//			commandBuffer->Commit();
//		}
//
//		// swap the back and front buffers.
//		swapChain->Present();
//		commandQueue->WaitComplete();
	}

	void LoadTestModel()
	{
//		tinyobj::ObjReader reader;
//		if (!reader.ParseFromFile("Resource/Meshes/bunny.obj"))
//		{
//			if (!reader.Error().empty())
//				JFLogError(reader.Error().c_str());
//			EXPECT_EQ(0, 1);
//		}
//
//		if (!reader.Warning().empty())
//		{
//			JFLogWarning(reader.Warning().c_str());
//		}
//
//		auto& attrib = reader.GetAttrib();
//		auto& shapes = reader.GetShapes();
//		auto& materials = reader.GetMaterials();
//
//		// Loop over shapes
//		for (size_t s = 0; s < shapes.size(); ++s)
//		{
//			JFArray<Vertex> vertices;
//			vertices.Reserve(shapes[s].mesh.num_face_vertices.size() * 3);
//
//			// Loop over faces(polygon)
//			size_t index_offset = 0;
//			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
//			{
//				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
//
//				// Loop over vertices in the face.
//				for (size_t v = 0; v < fv; ++v)
//				{
//					Vertex vertex{};
//
//					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
//
//					// access to vertex
//					vertex.pos = JFVector3(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
//										   attrib.vertices[3 * size_t(idx.vertex_index) + 1],
//										   attrib.vertices[3 * size_t(idx.vertex_index) + 2]);
//
//					// Check if `normal_index` is zero or positive. negative = no normal data
//					if (idx.normal_index >= 0) {
//						vertex.normal = JFVector3(attrib.normals[3 * size_t(idx.normal_index) + 0],
//												  attrib.normals[3 * size_t(idx.normal_index) + 1],
//												  attrib.normals[3 * size_t(idx.normal_index) + 2]);
//					}
//
//					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
//					/*if (idx.texcoord_index >= 0) {
//						tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
//						tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
//					}*/
//
//					// Optional: vertex colors
//					vertex.color = JFLinearColor(attrib.colors[3 * size_t(idx.vertex_index) + 0],
//												 attrib.colors[3 * size_t(idx.vertex_index) + 1],
//												 attrib.colors[3 * size_t(idx.vertex_index) + 2],
//												 1.f);
//
//					vertices.Add(vertex);
//				}
//				index_offset += fv;
//			}
//
//			JFObject<JFGPUBuffer> vertexBuffer = graphicsDevice->CreateGPUBuffer(vertices.Bytes(), JFGPUBuffer::CPUCacheMode::WriteCombined);
//			vertexBuffer->WriteData(vertices.Data(), vertices.Bytes());
//			staticMeshes.EmplaceAdd(std::move(vertices), vertexBuffer);
//		}
	}

private:
	//std::jthread loopThread;

	JFObject<JFWindow> window;
//	JFObject<JFGraphicsDevice> graphicsDevice;
//	JFObject<JFCommandQueue> commandQueue;
//	JFObject<JFSwapChain> swapChain;
//
//	JFObject<JFRenderPipeline> renderPipeline;
//
//	JFObject<JFTexture> whiteTexture;
//
//	JFObject<JFShader> vertexShader;
//	JFObject<JFShader> pixelShader;
//
//	JFCamera camera;
//	JFArray<StaticMesh> staticMeshes;
//	JFObject<JFGPUBuffer> constantsBuffer;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
