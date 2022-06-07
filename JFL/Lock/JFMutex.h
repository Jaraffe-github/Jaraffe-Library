//
//  File: JFMutex.h
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
    class JFL_API JFMutex final
    {
    public:
        JFMutex() = default;
        ~JFMutex() = default;

        void Lock() const;
        bool TryLock() const;
        void Unlock() const;

    private:
        JFMutex(const JFMutex&) = delete;
        JFMutex& operator = (const JFMutex&) = delete;

        mutable class JFL_API std::mutex lock;
    };
}