//
//  File: JFGApplication.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFGApplication.h"

using namespace JFG;

JFGApplication::JFGApplication()
	: testScene(nullptr)
{
	testScene = new JFGTestScene();
}

JFGApplication::~JFGApplication()
{
}

void JFGApplication::OnInitialize()
{
	JFASSERT_DEBUG(testScene);
	testScene->Initialize();

	loopThread = std::jthread(
		[this](std::stop_token stopTrigger)
		{
			while (!stopTrigger.stop_requested())
				Update();
		});
}

void JFGApplication::OnTerminate()
{
	JFASSERT_DEBUG(!loopThread.get_stop_token().stop_requested());
	loopThread.request_stop();
	loopThread.join();

	JFASSERT_DEBUG(testScene);
	testScene->Terminate();
}

void JFGApplication::Update()
{
	JFASSERT_DEBUG(testScene);
	testScene->Update();
	testScene->Render();
}
