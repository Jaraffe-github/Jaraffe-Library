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
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
