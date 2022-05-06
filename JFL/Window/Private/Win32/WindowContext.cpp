//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#if defined(_WIN32)
#include "WindowContext.h"

using namespace JFL;

WindowContext::WindowContext()
    : handle(nullptr)
{
}

void WindowContext::Create()
{
    // Initialize the window class.
    WNDCLASSEXW windowClass = { 0 };
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = ::GetModuleHandleW(NULL);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = WINDOW_CLASS_NAME;
    ::RegisterClassExW(&windowClass);

    handle = ::CreateWindowExW(0, WINDOW_CLASS_NAME, L"Jaraffe Library Window",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             nullptr, nullptr, ::GetModuleHandleW(NULL), nullptr);
    JFASSERT_DEBUG(handle);

    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw
    ::SetLastError(0);
    if (!::SetWindowLongPtrW(handle, GWLP_USERDATA, (LONG_PTR)this))
    {
        JFASSERT_DEBUG(::GetLastError() == 0);
    }
}

void WindowContext::Destory()
{
    JFASSERT_DEBUG(handle);
    ::PostMessageW(handle, WM_CLOSE, 0, 0);
    handle = NULL;
}

void WindowContext::Show()
{
    JFASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_SHOWNORMAL);
}

void WindowContext::Hide()
{
    JFASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_HIDE);
}

void* WindowContext::PlatformHandle() const
{
    JFASSERT_DEBUG(handle);
	return handle;
}

LRESULT WindowContext::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowContext* window = (WindowContext*)::GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if (window)
    {
        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    // Handle any messages the switch statement didn't.
    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}

#endif
