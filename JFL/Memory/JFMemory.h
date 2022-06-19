//
//  File: JFAllocator.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	struct JFDefaultAllocator
	{
		static void* Alloc(size_t s) { return std::malloc(s); }
		static void* Realloc(void* p, size_t s) { return std::realloc(p, s); }
		static void Free(void* p) { std::free(p); }
	};
}
