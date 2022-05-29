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

		graphicsDevice = JFGraphicsDevice::CreateGraphicsDevice();
		commandQueue = graphicsDevice->CreateCommandQueue();
		commandList = graphicsDevice->CreateCommandList();
		swapChain = commandQueue->CreateSwapChain(window);

		vertexBuffer = graphicsDevice->CreateGPUBuffer(50000, JFGPUBuffer::CPUCacheMode::WriteCombined);
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
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
