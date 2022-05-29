//
//  File: JFWindow.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFWindow.h"
#include "Private/WindowPlatform.h"

using namespace JFL;

JFWindow* JFWindow::CreatePlatformWindow()
{
	return Private::CreatePlatformWindow();
}
