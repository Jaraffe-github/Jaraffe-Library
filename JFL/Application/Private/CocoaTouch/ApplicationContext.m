//
//  File: ApplicationContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include "ApplicationContext.h"
#include <UIKit/UIKit.h>

using namespace JFL;

int ApplicationContext::MessageLoop()
{
    [UIApplication sharedApplication];
    while( CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.0001, true) == kCFRunLoopRunHandledSource);
    return 0;
}

#endif
#endif
