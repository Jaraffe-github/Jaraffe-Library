//
//  File: WindowContext.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFWindow.h"
#include "JFInclude.h"
#include <windows.h>

namespace JFL
{
	class Window : public JFWindow
	{
	public:
		Window();
		~Window() = default;

		void Create(const JFWindowDescriptor& descriptor) override;
		void Destory() override;

		void Show() override;
		void Hide() override;

		void* PlatformHandle() const override;

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND handle;
	};
}
