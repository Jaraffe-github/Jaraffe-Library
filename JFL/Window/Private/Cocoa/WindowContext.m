//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_OSX
#include "WindowContext.h"

using namespace JFL;

@interface WindowDelegate : NSObject<NSWindowDelegate>
@end

@implementation WindowDelegate

- (void)windowWillClose:(NSNotification *)notification
{
    [NSApp stop:nil];
}

@end

WindowContext::WindowContext()
    : window(nil)
    , view(nil)
{
}

void WindowContext::Create()
{
    NSRect rect = NSMakeRect(300, 300, 512, 512);
    window = [[NSWindow alloc] initWithContentRect:rect styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer:NO];
    [window setTitle: @"Jaraffe Library Window"];
    [window setReleasedWhenClosed:YES];
    
    view = [[NSView alloc] initWithFrame:[window backingAlignedRect:rect options:NSAlignAllEdgesOutward]];
    [window setContentView:view];
    [window setDelegate:[WindowDelegate alloc]];
}

void WindowContext::Destory()
{
    // ref counting.
    view = nil;
    window = nil;
}

void WindowContext::Show()
{
    [window setIsVisible:YES];
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