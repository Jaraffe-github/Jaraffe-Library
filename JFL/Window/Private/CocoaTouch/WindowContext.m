//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include "WindowContext.h"

using namespace JFL;

@interface ViewController : UIViewController
@end

@implementation ViewController

@end

WindowContext::WindowContext()
    : window(nil)
    , view(nil)
{
}

void WindowContext::Create()
{
    CGRect rect = [[UIScreen mainScreen] bounds];
    // CGRect nativeRect = [[UIScreen mainScreen] nativeBounds];
    // float scale = [[UIScreen mainScreen] scale];
    
    view = [[UIView alloc] initWithFrame:rect];
    
    ViewController* viewController = [[ViewController alloc] init];
    [viewController setView:view];

    window = [[UIWindow alloc] initWithFrame:rect];
    [window setRootViewController:viewController];
    [window setContentMode:UIViewContentModeScaleToFill];
    [window setBounds:rect];
}

void WindowContext::Destory()
{
    // ref counting.
    view = nil;
    window = nil;
}

void WindowContext::Show()
{
    [window makeKeyAndVisible];
}

void WindowContext::Hide()
{
    
}

void* WindowContext::PlatformHandle() const
{
    return nil;
}

#endif
#endif
