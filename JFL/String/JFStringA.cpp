//
//  File: JFStringA.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFStringA.h"
#include <fmt/args.h>
#include <fmt/format.h>

using namespace JFL;

JFStringA::JFStringA()
	: data(nullptr)
{}

JFStringA::JFStringA(char c, size_t len)
	: data(new char[len + 1])
{
	std::memset(data, c, len);
}

JFStringA::JFStringA(const char* c, size_t len)
	: data(nullptr)
{
	Append(c, len);
}

JFStringA::JFStringA(const JFStringA& str)
	: data(nullptr)
{
	Append(str);
}

JFStringA::JFStringA(JFStringA&& str) noexcept
	: data(nullptr)
{
	data = str.data;
	str.data = nullptr;
}

JFStringA::~JFStringA()
{
	if (data)
		delete data;
	data = nullptr;
}

JFStringA JFStringA::SubString(uint64_t index, size_t count) const
{
	if (data)
		return JFStringA(&data[index], count);
	return {};
}

JFStringA JFStringA::ReversedString() const
{
	JFStringA reveredString(*this);
	{
		size_t len = reveredString.Length();
		for (size_t i = 0; i < len / 2; ++i)
		{
			Swap(data[i], data[len - i - 1]);
		}
	}
	return reveredString;
}

JFStringA& JFStringA::Append(const char* c, size_t len)
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
			char* appendedChar = new char[totalLen + 1];
			{
				char* cursor = appendedChar;
				if (sourceLen > 0)
				{
					memcpy(cursor, data, sourceLen);
					cursor += sourceLen;
				}

				if (targetLen > 0)
				{
					memcpy(cursor, c, targetLen);
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

size_t JFStringA::Bytes() const
{
	return Length();
}

size_t JFStringA::Length() const
{
	size_t len = 0;
	if (data)
		for (; data[len]; ++len) {}
	return len;
}

char* JFStringA::Data() const
{
	return data;
}

JFStringA::operator const char* () const
{
	if (data)
		return data;
	return "";
}

JFStringA& JFStringA::operator=(const char* c)
{
    return Append(c);
}

JFStringA& JFStringA::operator=(const JFStringA& str)
{
	return Append(str);
}

JFStringA& JFStringA::operator=(JFStringA&& str) noexcept
{
	data = str.data;
	str.data = nullptr;
	return *this;
}
