//
//  File: JFWindow.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFWindow
	{
	public:
		virtual ~JFWindow() noexcept = default;

		static JFWindow* CreatePlatformWindow();

		virtual void Create() = 0;
		virtual void Destory() = 0;

		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void* PlatformHandle() const = 0;

	protected:
		JFWindow() = default;
	};
}
