//
//  File: JFWindow.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFWindow.h"
#include "Private/WindowPlatform.h"
#include "Container/JFContainer.h"

using namespace JFL;

JFWindow* JFWindow::CreatePlatformWindow()
{
	return Private::CreatePlatformWindow();
}

JFWindow::JFWindow()
	: width(1)
	, height(1)
{
}

uint32_t JFWindow::Width() const
{
	return width;
}

uint32_t JFWindow::Height() const
{
	return height;
}

float JFWindow::AspectRatio() const
{
	return static_cast<float>(width) / static_cast<float>(height);;
}

void JFWindow::AddWindowEventListener(EventListener listener, const WindowEventCallback& callback)
{
	JFScopedLock guard(eventLock);
	windowEventListeners.emplace(listener, callback);
}

void JFWindow::RemoveWindowEventListener(EventListener listener)
{
	JFScopedLock guard(eventLock);
	windowEventListeners.erase(listener);
}

void JFWindow::PostWindowEvent(const JFWindowEvent& windowEvent)
{
	switch (windowEvent.type)
	{
	case JFWindowEvent::Type::Create:
	case JFWindowEvent::Type::Close:
		break;
	case JFWindowEvent::Type::Resize:
		width = windowEvent.width;
		height = windowEvent.height;
		break;
	default:
		break;
	}

	JFArray<WindowEventCallback> callbacks;

	JFScopedLock guard(eventLock);
	callbacks.Reserve(windowEventListeners.size());
	for (const auto& [listener, callback] : windowEventListeners)
		callbacks.Add(callback);
	guard.Unlock();

	// broadcast.
	for (const auto callback : callbacks)
		callback(windowEvent);
}
