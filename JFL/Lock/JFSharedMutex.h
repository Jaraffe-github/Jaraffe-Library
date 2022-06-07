//
//  File: JFSharedMutex.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFL_API JFSharedMutex final
    {
    public:
        JFSharedMutex();
        ~JFSharedMutex();

        void Lock() const;
        bool TryLock() const;
        void Unlock() const;

        void LockShared() const;
        bool TryLockShared() const;
        void UnlockShared() const;

    private:
        JFSharedMutex(const JFSharedMutex&) = delete;
        JFSharedMutex& operator = (const JFSharedMutex&) = delete;

        mutable void* impl;
    };
}
