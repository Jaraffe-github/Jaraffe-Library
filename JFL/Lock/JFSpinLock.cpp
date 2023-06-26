//
//  File: JFSpinLock.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFSpinLock.h"

using namespace JFL;

void JFSpinLock::Lock() const
{
//    while (!TryLock())
//        std::this_thread::yield();
}

bool JFSpinLock::TryLock() const
{
    return !lock.test_and_set(std::memory_order_acquire);
}

void JFSpinLock::Unlock() const
{
    lock.clear(std::memory_order_release);
}
