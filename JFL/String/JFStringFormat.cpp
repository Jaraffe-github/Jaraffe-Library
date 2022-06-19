//
//  File: JFStringFormat.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFStringFormat.h"
#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <fmt/color.h>

using namespace JFL;

JFStringA JFStringFormat::FormatArray(const char* format, const std::vector<JFPrimitiveVariant>& arguments)
{
	fmt::dynamic_format_arg_store<fmt::buffer_context<char>> dynamicArguments;
	for (JFPrimitiveVariant v : arguments)
	{
		switch (v.ActiveType())
		{
		case JFPrimitiveVariant::Type::Boolean:
			dynamicArguments.push_back(v.Boolean());
			break;
		case JFPrimitiveVariant::Type::Int32:
			dynamicArguments.push_back(v.Int32());
			break;
		case JFPrimitiveVariant::Type::Int64:
			dynamicArguments.push_back(v.Int64());
			break;
		case JFPrimitiveVariant::Type::UInt32:
			dynamicArguments.push_back(v.UInt32());
			break;
		case JFPrimitiveVariant::Type::UInt64:
			dynamicArguments.push_back(v.UInt64());
			break;
		case JFPrimitiveVariant::Type::Float:
			dynamicArguments.push_back(v.Float());
			break;
		case JFPrimitiveVariant::Type::Double:
			dynamicArguments.push_back(v.Double());
			break;
		case JFPrimitiveVariant::Type::Char:
			dynamicArguments.push_back(v.Char());
			break;
		case JFPrimitiveVariant::Type::WChar:
			JFASSERT_DESC_DEBUG(false, "Char format doesn't support argument type to wchar_t.");
			dynamicArguments.push_back<const char*>("{Not supported Type}");
			break;
		}
	}

	return fmt::vformat(format, dynamicArguments).c_str();
}

JFStringW JFStringFormat::FormatArray(const wchar_t* format, const std::vector<JFPrimitiveVariant>& arguments)
{
	fmt::dynamic_format_arg_store<fmt::buffer_context<wchar_t>> dynamicArguments;
	for (JFPrimitiveVariant v : arguments)
	{
		switch (v.ActiveType())
		{
		case JFPrimitiveVariant::Type::Boolean:
			dynamicArguments.push_back(v.Boolean());
			break;
		case JFPrimitiveVariant::Type::Int32:
			dynamicArguments.push_back(v.Int32());
			break;
		case JFPrimitiveVariant::Type::Int64:
			dynamicArguments.push_back(v.Int64());
			break;
		case JFPrimitiveVariant::Type::UInt32:
			dynamicArguments.push_back(v.UInt32());
			break;
		case JFPrimitiveVariant::Type::UInt64:
			dynamicArguments.push_back(v.UInt64());
			break;
		case JFPrimitiveVariant::Type::Float:
			dynamicArguments.push_back(v.Float());
			break;
		case JFPrimitiveVariant::Type::Double:
			dynamicArguments.push_back(v.Double());
			break;
		case JFPrimitiveVariant::Type::Char:
			{
				std::string_view str(v.Char());
				size_t len = str.length();
				std::wstring strW(L'\0', static_cast<int>(len + 1));
				std::mbstowcs(strW.data(), str.data(), len);
				dynamicArguments.push_back(strW); // copy.
			}
			break;
		case JFPrimitiveVariant::Type::WChar:
			dynamicArguments.push_back(v.WChar());
			break;
		}
	}

	return fmt::vformat<wchar_t>(format, dynamicArguments).c_str();
}
