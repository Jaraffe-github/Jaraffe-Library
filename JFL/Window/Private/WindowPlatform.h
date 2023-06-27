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
#ifdef JFPLATFORM_WINDOWS
	namespace Win32
	{
		extern JFWindow* CreatePlatformWindow();
	}
	using namespace Win32;
#elif JFPLATFORM_MAC
    namespace Cocoa
    {
        extern JFWindow* CreatePlatformWindow();
    }
    using namespace Cocoa;
#elif JFPLATFORM_IOS
    namespace CocoaTouch
    {
        extern JFWindow* CreatePlatformWindow();
    }
    using namespace CocoaTouch;
#elif
    #error "Unsupported platform. Window creation not implemented."
#endif
}
