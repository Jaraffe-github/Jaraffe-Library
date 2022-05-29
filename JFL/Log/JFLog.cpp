//
//  File: JFLog.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
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
		case JFLogLevel::Debug:
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
		case JFLogLevel::Debug:
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


void JFL::JFLog(JFLogLevel logLevel, const char* format, const std::vector<JFLogVariant>& arguments)
{
	fmt::dynamic_format_arg_store<fmt::buffer_context<char>> dynamicArguments;
	for (JFLogVariant v : arguments)
	{
		switch (v.ActiveType())
		{
		case JFLogVariant::Type::Boolean:
			dynamicArguments.push_back(v.Boolean());
			break;
		case JFLogVariant::Type::Int32:
			dynamicArguments.push_back(v.Int32());
			break;
		case JFLogVariant::Type::Int64:
			dynamicArguments.push_back(v.Int64());
			break;
		case JFLogVariant::Type::UInt32:
			dynamicArguments.push_back(v.UInt32());
			break;
		case JFLogVariant::Type::UInt64:
			dynamicArguments.push_back(v.UInt64());
			break;
		case JFLogVariant::Type::Float:
			dynamicArguments.push_back(v.Float());
			break;
		case JFLogVariant::Type::Double:
			dynamicArguments.push_back(v.Double());
			break;
		case JFLogVariant::Type::Char:
			dynamicArguments.push_back(v.Char());
			break;
		case JFLogVariant::Type::WChar:
			JFASSERT_DESC_DEBUG(false, "Char format doesn't support argument type to wchar_t.");
			dynamicArguments.push_back<const char*>("{Not supported Type}");
			break;
		}
	}

	Private::LogPrint(logLevel, fmt::vformat(format, dynamicArguments).c_str());
}

void JFL::JFLog(JFLogLevel logLevel, const wchar_t* format, const std::vector<JFLogVariant>& arguments)
{
	fmt::dynamic_format_arg_store<fmt::buffer_context<wchar_t>> dynamicArguments;
	for (JFLogVariant v : arguments)
	{
		switch (v.ActiveType())
		{
		case JFLogVariant::Type::Boolean:
			dynamicArguments.push_back(v.Boolean());
			break;
		case JFLogVariant::Type::Int32:
			dynamicArguments.push_back(v.Int32());
			break;
		case JFLogVariant::Type::Int64:
			dynamicArguments.push_back(v.Int64());
			break;
		case JFLogVariant::Type::UInt32:
			dynamicArguments.push_back(v.UInt32());
			break;
		case JFLogVariant::Type::UInt64:
			dynamicArguments.push_back(v.UInt64());
			break;
		case JFLogVariant::Type::Float:
			dynamicArguments.push_back(v.Float());
			break;
		case JFLogVariant::Type::Double:
			dynamicArguments.push_back(v.Double());
			break;
		case JFLogVariant::Type::Char:
			{
				std::string_view str(v.Char());
				size_t len = str.length();
				std::wstring strW(L'\0', static_cast<int>(len + 1));
				std::mbstowcs(strW.data(), str.data(), len);
				dynamicArguments.push_back(strW); // copy.
			}
			break;
		case JFLogVariant::Type::WChar:
			dynamicArguments.push_back(v.WChar());
			break;
		}
	}

	Private::LogPrint(logLevel, fmt::vformat<wchar_t>(format, dynamicArguments).c_str());
}
