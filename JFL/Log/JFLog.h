//
//  File: JFLog.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFLogVariant.h"
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
	void JFLogInternal(JFLogLevel, const char*, const std::vector<JFLogVariant>&);
	void JFLogInternal(JFLogLevel, const wchar_t*, const std::vector<JFLogVariant>&);

	void JFLog(JFLogLevel logLevel, const char* format)
	{
		JFLogInternal(logLevel, format, std::vector<JFLogVariant>());
	}
	void JFLog(JFLogLevel logLevel, const wchar_t* format)
	{
		JFLogInternal(logLevel, format, std::vector<JFLogVariant>());
	}

	template<class... Args>
	void JFLog(JFLogLevel logLevel, const char* format, Args&&... args)
	{
		JFLogInternal(logLevel, format, std::vector<JFLogVariant>{JFLogVariant(std::forward<Args>(args))...});
	}
	template<class... Args>
	void JFLog(JFLogLevel logLevel, const wchar_t* format, Args&&... args)
	{
		JFLogInternal(logLevel, format, std::vector<JFLogVariant>{JFLogVariant(std::forward<Args>(args))...});
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