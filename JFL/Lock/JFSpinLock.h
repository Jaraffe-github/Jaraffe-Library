//
//  File: JFSpinLock.h
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
    class JFL_API JFSpinLock final
    {
    public:
        JFSpinLock() = default;
        ~JFSpinLock() = default;

        void Lock() const;
        bool TryLock() const;
        void Unlock() const;

    private:
        JFSpinLock(const JFSpinLock&) = delete;
        JFSpinLock& operator = (const JFSpinLock&) = delete;

        mutable struct JFL_API std::atomic_flag lock;
    };
}
