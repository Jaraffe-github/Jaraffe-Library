//
//  File: ApplicationPlatform.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFApplicationContextInterface.h"

#include "Win32/ApplicationContext.h"
#include "Cocoa/ApplicationContext.h"
#include "CocoaTouch/ApplicationContext.h"

JFL::JFApplicationContextInterface* CreateApplicationContext()
{
	return new JFL::ApplicationContext();
}
