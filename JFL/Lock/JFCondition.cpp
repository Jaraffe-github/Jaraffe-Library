//
//  File: JFCondition.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFCondition.h"

using namespace JFL;

void JFCondition::Lock() const
{
	lock.lock();
}

bool JFCondition::TryLock() const
{
	return lock.try_lock();
}

void JFCondition::Unlock() const
{
	lock.unlock();
}

void JFCondition::Signal() const noexcept
{
	condition.notify_one();
}

void JFCondition::Broadcast() const noexcept
{
	condition.notify_all();
}

void JFCondition::Wait() const
{
	std::unique_lock<std::mutex> ul(lock);
	condition.wait(ul);
}

void JFCondition::WaitTimout(double sec) const
{
	std::unique_lock<std::mutex> ul(lock);
	condition.wait_for(ul, std::chrono::duration<double>(sec));
}
