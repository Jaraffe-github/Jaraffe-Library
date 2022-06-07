//
//  File: JFSharedMutex.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFSharedMutex.h"
#include <shared_mutex>

using namespace JFL;

JFSharedMutex::JFSharedMutex()
    : impl(nullptr)
{
    impl = new std::shared_mutex();
}

JFSharedMutex::~JFSharedMutex()
{
    delete impl;
    impl = nullptr;
}

void JFSharedMutex::Lock() const
{
    reinterpret_cast<std::shared_mutex*>(impl)->lock();
}

bool JFSharedMutex::TryLock() const
{
    return reinterpret_cast<std::shared_mutex*>(impl)->try_lock();
}

void JFSharedMutex::Unlock() const
{
    reinterpret_cast<std::shared_mutex*>(impl)->unlock();
}

void JFSharedMutex::LockShared() const
{
    reinterpret_cast<std::shared_mutex*>(impl)->lock_shared();
}

bool JFSharedMutex::TryLockShared() const
{
    return reinterpret_cast<std::shared_mutex*>(impl)->try_lock_shared();
}

void JFSharedMutex::UnlockShared() const
{
    reinterpret_cast<std::shared_mutex*>(impl)->unlock_shared();
}
