//
//  File: JFWindowDescriptor.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "String/JFString.h"

namespace JFL
{
	struct JFWindowDescriptor
	{
		JFStringW title;

		// Window position based on Top Left
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t width = 516;
		uint32_t height = 516;

		// Settings
		bool centered : 1 = true;
		bool resizable : 1 = true;
		bool movable : 1 = true;
		bool minimizable : 1 = true;
		bool maximizable : 1 = true;
	};
}
