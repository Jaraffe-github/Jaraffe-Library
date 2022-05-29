//
//  File: JFLogVariant.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFLogVariant final
	{
	public:
		enum class Type : int
		{
			None = 0,
			Boolean,
			Int32,
			Int64,
			UInt32,
			UInt64,
			Long,
			ULong,
			Float,
			Double,
			Char,
			WChar,
		};

		JFLogVariant();
		JFLogVariant(const JFLogVariant& v) = default;
		JFLogVariant(JFLogVariant&& v) = default;
		explicit JFLogVariant(const bool v) noexcept;
		explicit JFLogVariant(const int32_t v) noexcept;
		explicit JFLogVariant(const int64_t v) noexcept;
		explicit JFLogVariant(const uint32_t v) noexcept;
		explicit JFLogVariant(const uint64_t v) noexcept;
		explicit JFLogVariant(const long v) noexcept;
		explicit JFLogVariant(const unsigned long v) noexcept;
		explicit JFLogVariant(const float v) noexcept;
		explicit JFLogVariant(const double v) noexcept;
		explicit JFLogVariant(const long double v) noexcept;
		explicit JFLogVariant(const char* v) noexcept;
		explicit JFLogVariant(const wchar_t* v) noexcept;
		explicit JFLogVariant(const void* v) noexcept; // to uintptr_t
		~JFLogVariant() = default;

		Type ActiveType() const { return activeType; };

		bool Boolean();
		int32_t Int32();
		int64_t Int64();
		uint32_t UInt32();
		uint64_t UInt64();
		long Long();
		unsigned long ULong();
		float Float();
		double Double();
		const char* Char();
		const wchar_t* WChar();

	private:
		Type activeType;
		unsigned char block[sizeof(void*)];
	};
}