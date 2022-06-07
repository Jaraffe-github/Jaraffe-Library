//
//  File: JFMutex.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFMutex.h"

using namespace JFL;

void JFMutex::Lock() const
{
    lock.lock();
}

bool JFMutex::TryLock() const
{
    return lock.try_lock();
}

void JFMutex::Unlock() const
{
    lock.unlock();
}
