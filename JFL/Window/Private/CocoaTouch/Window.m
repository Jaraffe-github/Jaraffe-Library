//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Window.h"

namespace JFL::Private::CocoaTouch
{
    JFWindow* CreatePlatformWindow()
    {
        return new Window();
    }
}

using namespace JFL;
using namespace JFL::Private::CocoaTouch;

@interface ViewController : UIViewController
@end

@implementation ViewController

@end

Window::Window()
    : window(nil)
    , view(nil)
{
}

void Window::Create(const JFWindowDescriptor& descriptor)
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

void Window::Destory()
{
    // ref counting.
    view = nil;
    window = nil;
}

void Window::Show()
{
    [window makeKeyAndVisible];
}

void Window::Hide()
{
    [window setHidden:YES];
}

JFStringW Window::Title() const
{
    NSString* title = [window rootViewController].title;
    const wchar_t* wideTitle = [title cStringUsingEncoding:NSUTF32LittleEndianStringEncoding];
    return JFStringW(wideTitle);
}

void SetTitle(const JFStringW& title)
{
    NSString* nsTitle = [NSString stringWithCharacters:title.Data() length:title.Length()];
    [[window rootViewController] setTitle:nsTitle];
}

void* Window::PlatformHandle() const
{
    return nil;
}
