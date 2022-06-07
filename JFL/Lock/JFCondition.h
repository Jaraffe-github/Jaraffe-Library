//
//  File: JFCondition.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include <mutex>

namespace JFL
{
    class JFL_API JFCondition final
    {
        template<class Clock, class Duration>
        using TimePoint = const std::chrono::time_point<Clock, Duration>;

    public:
        JFCondition() = default;
        ~JFCondition() = default;

        void Lock() const;
        bool TryLock() const;
        void Unlock() const;

        void Signal() const noexcept;
        void Broadcast() const noexcept;

        void Wait() const;
        void WaitTimout(double sec) const;

    private:
        JFCondition(const JFCondition&) = delete;
        JFCondition& operator = (const JFCondition&) = delete;

        mutable class JFL_API std::mutex lock;
        mutable class JFL_API std::condition_variable condition;
    };
}