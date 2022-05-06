//
//  File: ApplicationContext.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#if defined(_WIN32)
#include "ApplicationContext.h"
#include <Windows.h>

#pragma warning(push)
#pragma warning(disable: 4091) // 'typedef ': ignored on left of '' when no variable is declared
#include <dbghelp.h>
#pragma warning(pop)
#pragma comment(lib, "Dbghelp.lib")

namespace Private
{
    LONG WINAPI ExceptionCallback(__in struct _EXCEPTION_POINTERS* exceptioninfo)
    {
		// Create minidump file.
		if (exceptioninfo)
		{
			SYSTEMTIME st = { 0 };
			::GetLocalTime(&st);

			if (HANDLE handle = ::CreateFileW(L"JFApplicationDump.dmp",
											  GENERIC_WRITE,
											  0,
											  nullptr,
											  CREATE_ALWAYS,
											  FILE_ATTRIBUTE_NORMAL,
											  nullptr))
			{
				MINIDUMP_EXCEPTION_INFORMATION exceptionInfo = { 0 };
				exceptionInfo.ThreadId = ::GetCurrentThreadId();
				exceptionInfo.ExceptionPointers = exceptioninfo;
				exceptionInfo.ClientPointers = FALSE;

				// write
				::MiniDumpWriteDump(::GetCurrentProcess(), 
									::GetCurrentProcessId(),
									handle,
									MINIDUMP_TYPE::MiniDumpNormal,
									&exceptionInfo,
									nullptr, nullptr);
			}
		}

		return EXCEPTION_EXECUTE_HANDLER;
    }
}

using namespace JFL;

int ApplicationContext::MessageLoop()
{
    ::SetUnhandledExceptionFilter(Private::ExceptionCallback);

    MSG msg = {};
    while (auto ret = GetMessageW(&msg, nullptr, 0, 0))  // (ret == 0 indicates "exit program".)
    {
        if (ret > 0)  // (ret > 0 indicates a message that must be processed.)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else  // (ret == -1 indicates an error.)
        {
            // Handle or log the error; possibly exit.
        }
    }

	return static_cast<int>(msg.wParam);
}

#endif
