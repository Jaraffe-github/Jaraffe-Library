//
//  File: WindowContext.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "Window.h"
#include "Log/JFLog.h"

using namespace JFL;

namespace JFL::Private::Win32
{
    JFWindow* CreatePlatformWindow()
    {
        return new Window();
    }
}

Window::Window()
    : handle(nullptr)
{
}

void Window::Create(const JFWindowDescriptor& descriptor)
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

    // Current screen size.
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    DWORD windowExtraStyle = WS_EX_APPWINDOW;
    DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION;

    if (descriptor.resizable)
        windowStyle |= WS_THICKFRAME;

    if (descriptor.minimizable)
        windowStyle |= WS_MINIMIZEBOX;

    if (descriptor.maximizable)
        windowStyle |= WS_MAXIMIZEBOX;

    if (descriptor.minimizable || descriptor.maximizable)
        windowStyle |= WS_SYSMENU;

    // Store the current thread's DPI-awareness context
    DPI_AWARENESS_CONTEXT previousDpiContext = SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    RECT windowRect;
    windowRect.left = descriptor.x;
    windowRect.top = descriptor.y;
    windowRect.right = (long)descriptor.width;
    windowRect.bottom = (long)descriptor.height;

    AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowExtraStyle);

    handle = ::CreateWindowExW(0, WINDOW_CLASS_NAME,
                               descriptor.title, 
                               windowStyle,
                               0, 0,
                               windowRect.right - windowRect.left,
                               windowRect.bottom - windowRect.top, 
                               NULL, NULL, ::GetModuleHandleW(NULL), NULL);
    JFASSERT_DEBUG(handle);

    // Adjust size to match DPI
    int dpi = GetDpiForWindow(handle);
    if (dpi != USER_DEFAULT_SCREEN_DPI)
    {
        windowRect.bottom = MulDiv(windowRect.bottom, dpi, USER_DEFAULT_SCREEN_DPI);
        windowRect.right = MulDiv(windowRect.right, dpi, USER_DEFAULT_SCREEN_DPI);
    }

    // Center on screen
    if (descriptor.centered)
    {
        windowRect.left = (screenWidth - windowRect.right) / 2;
        windowRect.top = (screenHeight - windowRect.bottom) / 2;
	}

	SetWindowPos(handle, 0, windowRect.left, windowRect.top, (int)windowRect.right, (int)windowRect.bottom, 0);

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
        case WM_CREATE:
        {
            JFWindowEvent windowEvent{};
            windowEvent.type = JFWindowEvent::Type::Create;
            windowEvent.width = window->Width();
            windowEvent.height = window->Height();
            window->PostWindowEvent(windowEvent);
            return 0;
        }

        case WM_SIZE:
        {
            JFWindowEvent windowEvent{};
            windowEvent.type = JFWindowEvent::Type::Resize;
            windowEvent.width = LOWORD(lParam);
            windowEvent.height = HIWORD(lParam);
            window->PostWindowEvent(windowEvent);
            return 0;
        }

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            break;

        case WM_MOUSEWHEEL:
        {
            ((SHORT)HIWORD(wParam)) / (double)WHEEL_DELTA;
            return 0;
        }

        case WM_MOUSEHWHEEL:
        {
            // This message is only sent on Windows Vista and later
            // NOTE: The X-axis is inverted for consistency with macOS and X11
            -((SHORT)HIWORD(wParam) / (double)WHEEL_DELTA), 0.0;
            return 0;
        }

        case WM_MOUSEMOVE:
            break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
            break;

        case WM_CHAR:
        case WM_SYSCHAR:
            break;

        case WM_CLOSE:
        case WM_DESTROY:
        {
            JFWindowEvent windowEvent{};
            windowEvent.type = JFWindowEvent::Type::Close;
            windowEvent.width = window->Width();
            windowEvent.height = window->Height();
            window->PostWindowEvent(windowEvent);
            PostQuitMessage(0);
            return 0;
        }
        }
    }

    // Handle any messages the switch statement didn't.
    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}
