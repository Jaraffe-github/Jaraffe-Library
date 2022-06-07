//
//  File: JFScopedLock.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    template<class T>
    class JFScopedLock final
    {
    public:
        JFScopedLock(const T& lock)
            : lock(&lock)
        {
            this->lock->Lock();
        }

        ~JFScopedLock()
        {
            Unlock();
        }

        void Unlock()
        {
            if (lock)
            {
                lock->Unlock();
                lock = nullptr;
            }
        }

    private:
        const T* lock;
    };
}