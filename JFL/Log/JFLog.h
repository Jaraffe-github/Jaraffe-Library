//
//  File: JFLog.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "String/JFString.h"
#include <vector>

namespace JFL
{
	enum class JFLogLevel
	{
		Info,
		Verbose,
		Warning,
		Error
	};

	static void JFLog(JFLogLevel logLevel, const char* format);
	static void JFLog(JFLogLevel logLevel, const wchar_t* format);

	template<class... Args> void JFLog(JFLogLevel logLevel, const char* format, Args&&... args);
	template<class... Args> void JFLog(JFLogLevel logLevel, const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogInfo(const char* format, Args&&... args);
	template<class... Args> void JFLogInfo(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogVerbose(const char* format, Args&&... args);
	template<class... Args> void JFLogVerbose(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogWarning(const char* format, Args&&... args);
	template<class... Args> void JFLogWarning(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogError(const char* format, Args&&... args);
	template<class... Args> void JFLogError(const wchar_t* format, Args&&... args);

	//=============================================================================
	// Implementation)
	//=============================================================================
	void JFLogInternal(JFLogLevel, JFStringA&&);
	void JFLogInternal(JFLogLevel, JFStringW&&);

	void JFLog(JFLogLevel logLevel, const char* format)
	{
		JFLogInternal(logLevel, JFStringA(format));
	}
	void JFLog(JFLogLevel logLevel, const wchar_t* format)
	{
		JFLogInternal(logLevel, JFStringW(format));
	}

	template<class... Args>
	void JFLog(JFLogLevel logLevel, const char* format, Args&&... args)
	{
		JFLogInternal(logLevel, JFStringFormat::Format(format, std::forward<Args>(args)...));
	}
	template<class... Args>
	void JFLog(JFLogLevel logLevel, const wchar_t* format, Args&&... args)
	{
		JFLogInternal(logLevel, JFStringFormat::Format(format, std::forward<Args>(args)...));
	}

	template<class... Args>
	void JFLogInfo(const char* format, Args&&... args)
	{
		JFLog(JFLogLevel::Info, format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogInfo(const wchar_t* format, Args&&... args)
	{
		JFLog(JFLogLevel::Info, format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogVerbose(const char* format, Args&&... args)
	{
		JFLog(JFLogLevel::Debug, format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogVerbose(const wchar_t* format, Args&&... args)
	{
		JFLog(JFLogLevel::Debug, format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogWarning(const char* format, Args&&... args)
	{
		JFLog(JFLogLevel::Warning, format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogWarning(const wchar_t* format, Args&&... args)
	{
		JFLog(JFLogLevel::Warning, format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogError(const wchar_t* format, Args&&... args)
	{
		JFLog(JFLogLevel::Error, format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogError(const char* format, Args&&... args)
	{
		JFLog(JFLogLevel::Error, format, std::forward<Args>(args)...);
	}
}
