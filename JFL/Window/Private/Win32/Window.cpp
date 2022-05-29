//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "Window.h"

using namespace JFL;

namespace JFL::Private
{
    JFWindow* CreatePlatformWindow()
    {
        return new Window();
    }
}

Window::Window()
    : handle(nullptr)
    , width(0)
    , height(0)
{
}

void Window::Create()
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

void Window::Destory()
{
    JFASSERT_DEBUG(handle);
    ::PostMessageW(handle, WM_CLOSE, 0, 0);
    handle = NULL;
}

void Window::Show()
{
    JFASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_SHOWNORMAL);
}

void Window::Hide()
{
    JFASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_HIDE);
}

float Window::AspectRatio() const
{
    return static_cast<float>(width) / static_cast<float>(height);
}

void* Window::PlatformHandle() const
{
    JFASSERT_DEBUG(handle);
	return handle;
}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*)::GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if (window)
    {
        switch (message)
        {
        case WM_SIZE:
        {
            uint32_t width = LOWORD(lParam);
            uint32_t height = HIWORD(lParam);
            if (window->width != width || window->height != height)
            {
                window->width = width;
                window->height = height;
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    // Handle any messages the switch statement didn't.
    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}
