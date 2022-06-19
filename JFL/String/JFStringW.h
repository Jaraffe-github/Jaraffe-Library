//
//  File: JFStringW.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFStringW final
	{
	public:
		enum class Direction 
		{ 
			Front, 
			Back 
		};
		enum : size_t { All = (size_t)-2, Fail = (size_t)-1 };

		using Index = size_t;

		JFStringW();
		JFStringW(wchar_t c, size_t len);
		JFStringW(const wchar_t* c, size_t len = All);
		JFStringW(const char* c, size_t len = All);
		JFStringW(const JFStringW& str);
		JFStringW(JFStringW&& str) noexcept;
		~JFStringW();

		JFStringW& Append(const wchar_t* c, size_t len = All);

		size_t Bytes() const;
		size_t Length() const;

		template<Direction DIR = Direction::Front>
		Index Find(wchar_t c, Index begin = 0);

		JFStringW SubString(Index index, size_t count) const;
		JFStringW ReversedString();

		JFStringW& operator = (const wchar_t* c);
		JFStringW& operator = (const JFStringW& str);
		JFStringW& operator = (JFStringW&& str) noexcept;

		JFStringW operator + (const wchar_t* c);

		wchar_t* Data() const;
		operator const wchar_t* () const;

	private:
		wchar_t* data;
	};

	template<JFStringW::Direction DIR>
	JFStringW::Index JFStringW::Find(wchar_t c, Index begin)
	{
		if constexpr (DIR == Direction::Front)
		{
			size_t len = Length();
			for (size_t i = begin; i < len; ++i)
			{
				if (data[i] == c)
					return i;
			}
		}
		else
		{
			size_t len = Length();
			if (len > begin)
			{
				for (Index i = len - begin - 1; i >= 0; --i)
				{
					if (data[i] == c)
						return i;
				}
			}
		}
		return JFStringW::Fail;
	}
}
