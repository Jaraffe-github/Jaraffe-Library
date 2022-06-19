//
//  File: JFLog.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFLog.h"
#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <fmt/color.h>

using namespace JFL;

namespace Private
{
	using namespace JFL;

	std::string CurrentDateTime()
	{
		time_t now = time(0);
		struct tm tstruct = *localtime(&now);
		char buf[80];
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}

	std::string LogLevelToString(JFLogLevel logLevel)
	{
		switch (logLevel)
		{
		case JFLogLevel::Info:
			return "Info";
		case JFLogLevel::Verbose:
			return "Debug";
		case JFLogLevel::Warning:
			return "Warning";
		case JFLogLevel::Error:
			return "Error";
		}
		return "";
	}

	fmt::color LogLevelToColor(JFLogLevel logLevel)
	{
		switch (logLevel)
		{
		case JFLogLevel::Info:
			return fmt::color::light_green;
		case JFLogLevel::Verbose:
			return fmt::color::beige;
		case JFLogLevel::Warning:
			return fmt::color::green_yellow;
		case JFLogLevel::Error:
			return fmt::color::orange_red;
		}
		return fmt::color::white_smoke;
	}

	void LogPrint(JFLogLevel logLevel, const char* str)
	{
		auto style = fg(LogLevelToColor(logLevel));
		fmt::print(stdout, style, "[{}] [{}] {} \n",
				   CurrentDateTime(),
				   LogLevelToString(logLevel),
				   str);
	}

	void LogPrint(JFLogLevel logLevel, const wchar_t* str)
	{
		auto style = fg(LogLevelToColor(logLevel));
		fmt::print(stdout, style, "[{}] [{}] ",
				   CurrentDateTime(),
				   LogLevelToString(logLevel));
		fmt::print(stdout, style, L"{} \n", str);
	}
}

void JFL::JFLogInternal(JFLogLevel logLevel, JFStringA&& str)
{
	Private::LogPrint(logLevel, str);
}

void JFL::JFLogInternal(JFLogLevel logLevel, JFStringW&& str)
{
	Private::LogPrint(logLevel, str);
}
