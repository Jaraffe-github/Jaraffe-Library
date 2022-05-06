//
//  File: ApplicationContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_OSX
#include "ApplicationContext.h"
#include <Cocoa/Cocoa.h>

using namespace JFL;

int ApplicationContext::MessageLoop()
{
    NSApplication* app = [NSApplication sharedApplication];
    [app run];
    return 0;
}

#endif
#endif
