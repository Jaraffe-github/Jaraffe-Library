//
//  File: JFRecursiveMutex.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once

#pragma once
#include "JFInclude.h"
#include <mutex>

namespace JFL
{
    class JFL_API JFRecursiveMutex final
    {
    public:
        JFRecursiveMutex() = default;
        ~JFRecursiveMutex() = default;

        void Lock() const;
        bool TryLock() const;
        void Unlock() const;

    private:
        JFRecursiveMutex(const JFRecursiveMutex&) = delete;
        JFRecursiveMutex& operator = (const JFRecursiveMutex&) = delete;

        mutable class JFL_API std::recursive_mutex lock;
    };
}