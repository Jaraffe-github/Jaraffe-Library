//
//  File: WindowContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#if defined(_WIN32)
#include "JFInclude.h"
#include "../../JFWindowContextInterface.h"
#include <windows.h>

namespace JFL
{
	class WindowContext : public JFWindowContextInterface
	{
	public:
		WindowContext();
		~WindowContext() = default;

		void Create() override;
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

#endif
