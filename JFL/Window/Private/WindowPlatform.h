//
//  File: WindowPlatform.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFWindowContextInterface.h"

#include "Win32/WindowContext.h"
#include "Cocoa/WindowContext.h"
#include "CocoaTouch/WindowContext.h"

JFL::JFWindowContextInterface* CreateWindowContext()
{
	return new JFL::WindowContext();
}
