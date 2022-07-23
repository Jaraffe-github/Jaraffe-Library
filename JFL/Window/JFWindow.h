//
//  File: JFWindow.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "Lock/JFLock.h"
#include "String/JFStringW.h"
#include "JFWindowEvent.h"
#include "JFWindowDescriptor.h"
#include <functional>
#include <map>

namespace JFL
{
	class JFL_API JFWindow : public JFRefCounter
	{
	public:
		using EventListener = const void*;
		using WindowEventCallback = std::function<void(const JFWindowEvent&)>;

		virtual ~JFWindow() noexcept = default;

		static JFWindow* CreatePlatformWindow();

		virtual void Create(const JFWindowDescriptor& descriptor) = 0;
		virtual void Destory() = 0;

		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void* PlatformHandle() const = 0;

		uint32_t Width() const;
		uint32_t Height() const;
		float AspectRatio() const;

		void AddWindowEventListener(EventListener listener, const WindowEventCallback& callback);
		void RemoveWindowEventListener(EventListener listener);

	protected:
		JFWindow();

		void PostWindowEvent(const JFWindowEvent& windowEvent);

		uint32_t width;
		uint32_t height;

		JFSpinLock eventLock;
		JFL_API std::map<EventListener, WindowEventCallback> windowEventListeners;
	};
}
