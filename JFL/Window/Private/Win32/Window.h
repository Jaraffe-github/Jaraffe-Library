//
//  File: WindowContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
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

		void Create() override;
		void Destory() override;

		void Show() override;
		void Hide() override;

		uint32_t Width() const override { return width; }
		uint32_t Height() const override { return height; }
		float AspectRatio() const override;

		void* PlatformHandle() const override;

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND handle;

		uint32_t width;
		uint32_t height;
	};
}
