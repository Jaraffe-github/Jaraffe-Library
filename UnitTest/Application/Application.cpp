#include "gtest/gtest.h"
#include "JFL.h"
#include <thread>

using namespace JFL;

class TestApplication : public JFApplication
{
public:
	TestApplication()
		: window(nullptr)
		, graphicsDevice(nullptr)
	{}

	void OnInitialize() override
	{
		window = JFWindow::CreatePlatformWindow();
		window->Create();
		window->Show();

		graphicsDevice = JFGraphicsDevice::CreateGraphicsDevice(JFL::JFGraphicsType::Direct3D12);
		commandQueue = graphicsDevice->CreateCommandQueue();
		swapChain = commandQueue->CreateSwapChain(window);

		vertexBuffer = graphicsDevice->CreateGPUBuffer(50000, JFGPUBuffer::CPUCacheMode::WriteCombined);

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

		vertexShader = graphicsDevice->CreateShader(L"Resource/SimpleShader.hlsl", "VS", JFShader::StageType::Vertex);
		pixelShader = graphicsDevice->CreateShader(L"Resource/SimpleShader.hlsl", "PS", JFShader::StageType::Fragment);

		JFRenderPipelineDescriptor descriptor{};
		descriptor.sampleCount = 1;
		descriptor.vertexShader = vertexShader;
		descriptor.fragmentShader = pixelShader;
		descriptor.vertexDescriptor.attributes = {
			{JFVertexFormat::Float3, "POSITION", 0, 0},
			{JFVertexFormat::Float3, "NORMAL", 0, 12 },
			{JFVertexFormat::Float4, "COLOR", 0, 24 },
		};
		descriptor.colorAttachments = {{ JFPixelFormat::RGBA8Unorm, false }};
		descriptor.depthStencilAttachmentPixelFormat = JFPixelFormat::Depth24UnormStencil8;
		descriptor.inputPrimitiveTopology = JFPrimitiveTopologyType::Triangle;

		renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);

		loopThread = std::jthread([this](std::stop_token token) 
		{
			while (!token.stop_requested())
			{
				Update();
				Draw();
			}
		});
	}

	void OnTerminate() override
	{
		loopThread.request_stop();
		loopThread.join();
	}

	void Update()
	{

	}

	void Draw()
	{
		if (JFObject<JFCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
		{
			if (JFObject<JFRenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
			{
				JFViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
				encoder->SetViewport(viewport);

				JFRect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
				encoder->SetScissorRect(scissorRect);

				encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), JFLinearColor::green);
				encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), JFRenderCommandEncoder::DepthStencilClearFlag::All, 1.f, 0);

				encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

				encoder->EndEncoding();
			}

			commandBuffer->Commit();
		}

		swapChain->Present();
		commandQueue->WaitComplete();
	}

private:
	std::jthread loopThread;

	JFObject<JFWindow> window;
	JFObject<JFGraphicsDevice> graphicsDevice;
	JFObject<JFCommandQueue> commandQueue;
	JFObject<JFSwapChain> swapChain;

	JFObject<JFRenderPipeline> renderPipeline;

	JFObject<JFGPUBuffer> vertexBuffer;
	JFObject<JFTexture> whiteTexture;

	JFObject<JFShader> vertexShader;
	JFObject<JFShader> pixelShader;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
