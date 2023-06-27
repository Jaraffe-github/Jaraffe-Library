//
//  File: JFSpinLock.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFSpinLock.h"

using namespace JFL;

JFSpinLock::JFSpinLock()
{
#if defined(JFPLATFORM_LINUX)
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
#endif
}

JFSpinLock::~JFSpinLock()
{
#if defined(JFPLATFORM_LINUX)
	pthread_spin_destroy(&lock);
#endif
}

void JFSpinLock::Lock() const
{
#if defined(JFPLATFORM_LINUX)
	pthread_spin_lock(&lock);
#else
	while (!TryLock())
		std::this_thread::yield();
#endif
}

bool JFSpinLock::TryLock() const
{
#if defined(JFPLATFORM_LINUX)
	return pthread_spin_trylock(&lock);
#else
	return !lock.test_and_set(std::memory_order_acquire);
#endif
}

void JFSpinLock::Unlock() const
{
#if defined(JFPLATFORM_LINUX)
	pthread_spin_unlock(&lock);
#else
	lock.clear(std::memory_order_release);
#endif
}
