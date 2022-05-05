#include "gtest/gtest.h"
#include "JFL.h"

using namespace JFL;

class TestApplication : public JFL::JFApplication
{
public:
	TestApplication()
		: window(nullptr)
	{}

	void OnInitialize() override
	{
		window = new JFWindow();
		window->Create();
		window->Show();
	}

	void OnTerminate() override
	{
		delete window;
		window = nullptr;
	}

private:
	JFWindow* window;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
