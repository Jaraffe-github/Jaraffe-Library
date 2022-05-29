//
//  File: JFRefCounter.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFRefCounter.h"

using namespace JFL;

JFRefCounter::JFRefCounter()
	: refCount(0)
{
}

JFRefCounter::~JFRefCounter() noexcept
{
	JFASSERT_DEBUG(refCount == 0);
}

uint32_t JFRefCounter::AddRef()
{
	return ++refCount;
}

uint32_t JFRefCounter::Release()
{
	return --refCount;
}

uint32_t JFRefCounter::RefCount() const
{
	return refCount;
}
