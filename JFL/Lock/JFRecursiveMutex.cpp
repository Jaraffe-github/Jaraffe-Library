//
//  File: JFRecursiveMutex.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFRecursiveMutex.h"

using namespace JFL;

void JFRecursiveMutex::Lock() const
{
    lock.lock();
}

bool JFRecursiveMutex::TryLock() const
{
    return lock.try_lock();
}

void JFRecursiveMutex::Unlock() const
{
    lock.unlock();
}
