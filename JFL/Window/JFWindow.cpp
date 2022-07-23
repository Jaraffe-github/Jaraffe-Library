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

namespace JFL::Private
{
	struct WindowContext
	{
		JFSpinLock eventLock;
		std::map<JFWindow::EventListener, JFWindow::WindowEventCallback> windowEventListeners;
	};
}

JFWindow* JFWindow::CreatePlatformWindow()
{
	return Private::CreatePlatformWindow();
}

JFWindow::JFWindow()
	: width(1)
	, height(1)
{
	context = new Private::WindowContext();
}

JFWindow::~JFWindow() noexcept
{
	JFASSERT(context);
	if (context)
	{
		delete context;
		context = nullptr;
	}
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
	JFScopedLock guard(context->eventLock);
	context->windowEventListeners.emplace(listener, callback);
}

void JFWindow::RemoveWindowEventListener(EventListener listener)
{
	JFScopedLock guard(context->eventLock);
	context->windowEventListeners.erase(listener);
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

	JFScopedLock guard(context->eventLock);
	callbacks.Reserve(context->windowEventListeners.size());
	for (const auto& [listener, callback] : context->windowEventListeners)
		callbacks.Add(callback);
	guard.Unlock();

	// broadcast.
	for (const auto callback : callbacks)
		callback(windowEvent);
}
