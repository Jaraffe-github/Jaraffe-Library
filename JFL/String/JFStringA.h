//
//  File: JFStringA.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFStringA final
	{
	public:
		enum class Direction
		{
			Front,
			Back
		};
		enum : size_t { All = (size_t)-2, Fail = (size_t)-1 };

		using Index = size_t;
		
		JFStringA();
		JFStringA(char c, size_t len);
		JFStringA(const char* c, size_t len = All);
		JFStringA(const JFStringA& str);
		JFStringA(JFStringA&& str) noexcept;
		~JFStringA();

		JFStringA& Append(const char* c, size_t len = All);

		size_t Bytes() const;
		size_t Length() const;

		template<Direction DIR = Direction::Front>
		Index Find(char c, Index begin = 0);

		JFStringA SubString(uint64_t index, size_t count) const;
		JFStringA ReversedString() const;

		JFStringA& operator = (const char* c);
		JFStringA& operator = (const JFStringA& str);
		JFStringA& operator = (JFStringA&& str) noexcept;

		char* Data() const;
		operator const char* () const;

	private:
		char* data;
	};

	template<JFStringA::Direction DIR>
	JFStringA::Index JFStringA::Find(char c, Index begin)
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
		return JFStringA::Fail;
	}
}
