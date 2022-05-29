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
		Debug,
		Warning,
		Error
	};

	template<JFLogLevel> void JFLog(const char* format);
	template<JFLogLevel> void JFLog(const wchar_t* format);

	template<JFLogLevel, class... Args> void JFLog(const char* format, Args&&... args);
	template<JFLogLevel, class... Args> void JFLog(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogInfo(const char* format, Args&&... args);
	template<class... Args> void JFLogInfo(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogDebug(const char* format, Args&&... args);
	template<class... Args> void JFLogDebug(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogWarning(const char* format, Args&&... args);
	template<class... Args> void JFLogWarning(const wchar_t* format, Args&&... args);

	template<class... Args> void JFLogError(const char* format, Args&&... args);
	template<class... Args> void JFLogError(const wchar_t* format, Args&&... args);

	//=============================================================================
	// Implementation)
	//=============================================================================
	void JFLog(JFLogLevel, const char*, const std::vector<JFLogVariant>&);
	void JFLog(JFLogLevel, const wchar_t*, const std::vector<JFLogVariant>&);

	template<JFLogLevel LogLevel>
	void JFLog(const char* format)
	{
		JFLog(LogLevel, format, std::vector<JFLogVariant>());
	}
	template<JFLogLevel LogLevel>
	void JFLog(const wchar_t* format)
	{
		JFLog(LogLevel, format, std::vector<JFLogVariant>());
	}

	template<JFLogLevel LogLevel, class... Args>
	void JFLog(const char* format, Args&&... args)
	{
		JFLog(LogLevel, format, std::vector<JFLogVariant>{JFLogVariant(std::forward<Args>(args))...});
	}
	template<JFLogLevel LogLevel, class... Args>
	void JFLog(const wchar_t* format, Args&&... args)
	{
		JFLog(LogLevel, format, std::vector<JFLogVariant>{JFLogVariant(std::forward<Args>(args))...});
	}

	template<class... Args>
	void JFLogInfo(const char* format, Args&&... args)
	{
		JFLog<JFLogLevel::Info>(format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogInfo(const wchar_t* format, Args&&... args)
	{
		JFLog<JFLogLevel::Info>(format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogDebug(const char* format, Args&&... args)
	{
		JFLog<JFLogLevel::Debug>(format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogDebug(const wchar_t* format, Args&&... args)
	{
		JFLog<JFLogLevel::Debug>(format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogWarning(const char* format, Args&&... args)
	{
		JFLog<JFLogLevel::Warning>(format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogWarning(const wchar_t* format, Args&&... args)
	{
		JFLog<JFLogLevel::Warning>(format, std::forward<Args>(args)...);
	}

	template<class... Args>
	void JFLogError(const wchar_t* format, Args&&... args)
	{
		JFLog<JFLogLevel::Error>(format, std::forward<Args>(args)...);
	}
	template<class... Args>
	void JFLogError(const char* format, Args&&... args)
	{
		JFLog<JFLogLevel::Error>(format, std::forward<Args>(args)...);
	}
}