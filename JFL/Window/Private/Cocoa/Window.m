//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Window.h"

namespace JFL::Private::Cocoa
{
    JFWindow* CreatePlatformWindow()
    {
        return new Window();
    }
}

using namespace JFL;
using namespace JFL::Private::Cocoa;

@interface WindowDelegate : NSObject<NSWindowDelegate>
@end

@implementation WindowDelegate

- (void)windowWillClose:(NSNotification *)notification
{
    [NSApp stop:nil];
}

@end

Window::Window()
    : window(nil)
    , view(nil)
{
}

void Window::Create(const JFWindowDescriptor& descriptor)
{
    NSRect rect = NSMakeRect(300, 300, 512, 512);
    window = [[NSWindow alloc] initWithContentRect:rect styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer:NO];
    [window setTitle: @"Jaraffe Library Window"];
    [window setReleasedWhenClosed:YES];
    
    view = [[NSView alloc] initWithFrame:[window backingAlignedRect:rect options:NSAlignAllEdgesOutward]];
    [window setContentView:view];
    [window setDelegate:[WindowDelegate alloc]];
}

void Window::Destory()
{
    // ref counting.
    view = nil;
    window = nil;
}

void Window::Show()
{
    [window setIsVisible:YES];
}

void Window::Hide()
{
    
}

JFStringW Window::Title() const
{
    return {};
}

void Window::SetTitle(const JFStringW& title)
{
    
}

void* Window::PlatformHandle() const
{
    return nil;
}
