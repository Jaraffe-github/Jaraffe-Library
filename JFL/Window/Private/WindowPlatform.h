//
//  File: WindowPlatform.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFWindow.h"

#if !defined(_WIN32)
#include <TargetConditionals.h>
#endif

namespace JFL::Private
{
#if defined(_WIN32)
	namespace Win32
	{
		extern JFWindow* CreatePlatformWindow();
	}
	using namespace Win32;
#endif

#if TARGET_OS_MAC
    namespace Cocoa
    {
        extern JFWindow* CreatePlatformWindow();
    }
    using namespace Cocoa;
#elif TARGET_OS_IOS
    namespace CocoaTouch
    {
        extern JFWindow* CreatePlatformWindow();
    }
    using namespace CocoaTouch;
#endif
}
