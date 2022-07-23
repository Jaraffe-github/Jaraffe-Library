//
//  File: JFWindowEvent.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVirtualKeyCode.h"

struct JFWindowEvent
{
	enum class Type
	{
		Create = 0,
		Close,
		Resize,
	};

	Type type;
	uint32_t width;
	uint32_t height;
};

struct JFMouseEvent
{
	enum class Type
	{
		Down = 0,
		Up,
		Move,
		Wheel,
	};

	Type type;
};

struct JFKeyboardEvent
{
	JFVirtualKeyCode keyCode;
};
