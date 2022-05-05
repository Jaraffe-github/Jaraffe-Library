//
//  File: ApplicationPlatform.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFApplicationContextInterface.h"

#if defined(_WIN32)
#include "Win32/ApplicationContext.h"
#endif

JFL::JFApplicationContextInterface* CreateApplicationContext()
{
	return new JFL::ApplicationContext();
}
