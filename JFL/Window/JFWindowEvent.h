//
//  File: JFWindowEvent.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once

struct JFWindowEvent
{
	enum class Type
	{
		None = 0,

		Create,
		Close,
		Resize,
	};

	Type type;
	uint32_t width;
	uint32_t height;
};

struct JFMouseEvent
{

};

struct JFKeyboardEvent
{

};
