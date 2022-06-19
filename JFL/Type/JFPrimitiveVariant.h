//
//  File: JFPrimitiveVariant.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFPrimitiveVariant final
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

		JFPrimitiveVariant();
		JFPrimitiveVariant(const JFPrimitiveVariant& v) = default;
		JFPrimitiveVariant(JFPrimitiveVariant&& v) = default;
		explicit JFPrimitiveVariant(const bool v) noexcept;
		explicit JFPrimitiveVariant(const int32_t v) noexcept;
		explicit JFPrimitiveVariant(const int64_t v) noexcept;
		explicit JFPrimitiveVariant(const uint32_t v) noexcept;
		explicit JFPrimitiveVariant(const uint64_t v) noexcept;
		explicit JFPrimitiveVariant(const long v) noexcept;
		explicit JFPrimitiveVariant(const unsigned long v) noexcept;
		explicit JFPrimitiveVariant(const float v) noexcept;
		explicit JFPrimitiveVariant(const double v) noexcept;
		explicit JFPrimitiveVariant(const long double v) noexcept;
		explicit JFPrimitiveVariant(const char* v) noexcept;
		explicit JFPrimitiveVariant(const wchar_t* v) noexcept;
		explicit JFPrimitiveVariant(const void* v) noexcept; // to uintptr_t
		~JFPrimitiveVariant() = default;

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
