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
	}

	void OnTerminate() override
	{
		delete graphicsDevice;
		graphicsDevice = nullptr;

		delete window;
		window = nullptr;
	}

private:
	JFWindow* window;
	JFGraphicsDevice* graphicsDevice;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
