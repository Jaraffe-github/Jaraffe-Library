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
			if (JFObject<JFRenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder())
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

	JFObject<JFGPUBuffer> vertexBuffer;
	JFObject<JFTexture> whiteTexture;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
