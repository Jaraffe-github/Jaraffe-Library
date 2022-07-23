//
//  File: WindowPlatform.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFWindow.h"

namespace JFL::Private
{
#if defined(_WIN32)
	namespace Win32
	{
		extern JFWindow* CreatePlatformWindow();
	}
	using namespace Win32;
#endif
}
