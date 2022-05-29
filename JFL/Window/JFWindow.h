//
//  File: JFWindow.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"

namespace JFL
{
	class JFL_API JFWindow : public JFRefCounter
	{
	public:
		virtual ~JFWindow() noexcept = default;

		static JFWindow* CreatePlatformWindow();

		virtual void Create() = 0;
		virtual void Destory() = 0;

		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual uint32_t Width() const = 0;
		virtual uint32_t Height() const = 0;
		virtual float AspectRatio() const = 0;

		virtual void* PlatformHandle() const = 0;

	protected:
		JFWindow() = default;
	};
}
