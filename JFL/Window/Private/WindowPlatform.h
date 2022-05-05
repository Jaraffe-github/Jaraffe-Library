//
//  File: WindowPlatform.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFWindowContextInterface.h"

#if defined(_WIN32)
#include "Win32/WindowContext.h"
#endif

JFL::JFWindowContextInterface* CreateWindowContext()
{
	return new JFL::WindowContext();
}
