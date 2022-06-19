//
//  File: JFStringW.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFStringW.h"
#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <locale>
#include <codecvt>

using namespace JFL;

JFStringW::JFStringW()
	: data(nullptr)
{
}

JFStringW::JFStringW(wchar_t c, size_t len)
	: data(new wchar_t[len + 1])
{
	if (len)
		std::wmemset(data, c, len);
}

JFStringW::JFStringW(const wchar_t* c, size_t len)
	: data(nullptr)
{
	Append(c, len);
}

JFStringW::JFStringW(const char* c, size_t len)
	: data(nullptr)
{
	if (len)
	{
		size_t requiredSize = std::mbstowcs(nullptr, c, len);
		data = new wchar_t[requiredSize + 1];
		std::mbstowcs(data, c, requiredSize + 1);
	}
}

JFStringW::JFStringW(const JFStringW& str)
	: data(nullptr)
{
	Append(str);
}

JFStringW::JFStringW(JFStringW&& str) noexcept
	: data(nullptr)
{
	data = str.data;
	str.data = nullptr;
}

JFStringW::~JFStringW()
{
	if (data)
		delete data;
	data = nullptr;
}

JFStringW JFStringW::SubString(Index index, size_t count) const
{
	if (data)
		return JFStringW(&data[index], count);
	return {};
}

JFStringW JFStringW::ReversedString()
{
	JFStringW reveredString(*this);
	{
		size_t len = reveredString.Length();
		for (size_t i = 0; i < len / 2; ++i)
		{
			Swap(data[i], data[len - i - 1]);
		}
	}
	return reveredString;
}

JFStringW& JFStringW::Append(const wchar_t* c, size_t len)
{
	if (c)
	{
		size_t sourceLen = Length();
		size_t targetLen = 0;
		while (c[targetLen] && targetLen < len)
			++targetLen;

		size_t totalLen = sourceLen + targetLen;
		if (totalLen > 0)
		{
			wchar_t* appendedChar = new wchar_t[totalLen + 1];
			{
				wchar_t* cursor = appendedChar;
				if (sourceLen > 0)
				{
					memcpy(cursor, data, sourceLen * sizeof(wchar_t));
					cursor += sourceLen;
				}

				if (targetLen > 0)
				{
					memcpy(cursor, c, targetLen * sizeof(wchar_t));
					cursor += targetLen;
				}
				*cursor = '\0';
			}

			if (data)
				delete data;
			data = appendedChar;
		}
	}
	return *this;
}

size_t JFStringW::Length() const
{
	size_t len = 0;
	if (data)
		for (; data[len]; ++len) {}
	return len;
}

size_t JFStringW::Bytes() const
{
	return Length() * sizeof(wchar_t);
}

JFStringW& JFStringW::operator=(const wchar_t* c)
{
	return Append(c);
}

JFStringW& JFStringW::operator=(const JFStringW& str)
{
	return Append(str);
}

JFStringW& JFStringW::operator=(JFStringW&& str) noexcept
{
	data = str.data;
	str.data = nullptr;
	return *this;
}

JFStringW JFStringW::operator+(const wchar_t* c)
{
	JFStringW str(*this);
	str.Append(c);
	return str;
}

wchar_t* JFStringW::Data() const
{
	return data;
}

JFStringW::operator const wchar_t* () const
{
	if (data)
		return data;
	return L"";
}
