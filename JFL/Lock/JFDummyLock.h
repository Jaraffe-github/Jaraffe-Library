//
//  File: JFDummyLock.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    // Empty class.
    class JFDummyLock final
    {
    public:
        JFDummyLock() = default;
        ~JFDummyLock() = default;

        void Lock() const {}
        bool TryLock() const { return true; }
        void UnLock() const {}

    private:
        JFDummyLock(const JFDummyLock&) = delete;
        JFDummyLock& operator = (const JFDummyLock&) = delete;
    };
}