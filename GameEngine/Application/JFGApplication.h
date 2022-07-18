//
//  File: JFGApplication.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFGInclude.h"
#include "JFL.h"
#include "Scene/JFGTestScene.h"
#include <thread>

namespace JFG
{
	class JFGApplication final : public JFL::JFApplication
	{
	public:
		JFGApplication();
		~JFGApplication();

	protected:
		void OnInitialize() override;
		void OnTerminate() override;

		void Update();

	private:
		std::jthread loopThread;

		JFObject<JFGTestScene> testScene;
	};
}