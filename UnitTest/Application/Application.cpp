#include "gtest/gtest.h"
#include "JFL.h"

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

		graphicsDevice = JFGraphicsDevice::CreateGraphicsDevice(JFL::JFGraphicsType::Vulkan);
		commandQueue = graphicsDevice->CreateCommandQueue();
		commandList = graphicsDevice->CreateCommandList();
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
	}

	void OnTerminate() override
	{
	}

private:
	JFObject<JFWindow> window;
	JFObject<JFGraphicsDevice> graphicsDevice;
	JFObject<JFCommandQueue> commandQueue;
	JFObject<JFCommandList> commandList;
	JFObject<JFSwapChain> swapChain;

	JFObject<JFGPUBuffer> vertexBuffer;
	JFObject<JFTexture> whiteTexture;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
