//
//  File: JFInclude.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once

#define NOMINMAX
#include <cstdint>
#include <cassert>
#include <cmath>
#include <memory>

#if defined(_WIN32)
	#define JFPLATFORM_WINDOWS 1
#elif defined(__linux__)
	#define JFPLATFORM_LINUX 1
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#define JFPLATFORM_APPLE 1
	
	#if TARGET_OS_MAC
		#define JFPLATFORM_MAC
	#elif TARGET_OS_IOS
		#define JFPLATFORM_IOS
	#endif
#endif

struct JFLibraryVersion
{
	enum { Major = 0 };
	enum { Minor = 0 };
	enum { Patch = 0 };
};

#ifdef JFL_DYNAMIC
#   ifdef DLL_EXPORTS
#       define JFL_API __declspec(dllexport)
#   else
#       define JFL_API __declspec(dllimport)
#   endif
#else
#    define JFL_API
#endif

#define WINDOW_CLASS_NAME L"JFWindowClass"

#define JF_NOOP								(void)0;
#define JFASSERT(expr)						assert(expr)
#define JFASSERT_DESC(expr, desc)			assert(((void)desc, expr))

#if defined(_DEBUG)
#	define JFASSERT_DEBUG(expr)				JFASSERT(expr)
#	define JFASSERT_DESC_DEBUG(expr, desc)	JFASSERT_DESC(expr, desc)
#else
#	define JFASSERT_DEBUG(expr)				JF_NOOP
#	define JFASSERT_DESC_DEBUG(expr, desc)	JF_NOOP
#endif

namespace JFL
{
	template<class T>
	void Swap(T& a, T& b) noexcept
	{
		T temp(std::move(a));
		a = std::move(b);
		b = std::move(temp);
	}

	namespace JFNumeric
	{
		static constexpr float PI = 3.14159265358979323846f;
		static constexpr float DEG_TO_RAD = PI / 180.f;
		static constexpr float RAD_TO_DEG = 180.f / PI;

		constexpr float DegreesToRadians(float degrees)
		{
			return degrees * DEG_TO_RAD;
		}

		constexpr float RadiansToDegrees(float radians)
		{
			return radians * RAD_TO_DEG;
		}

		template<class T>
		concept Arithmetic = std::is_arithmetic_v<T>;

		template<Arithmetic T>
		constexpr decltype(auto) Abs(T v) noexcept
		{
			return v > static_cast<T>(0) ? v : v * static_cast<T>(-1);
		}

		template<std::floating_point T>
		constexpr bool IsClose(T a, T b, T tolerance = (T)1.0e-6)
		{
			return Abs(a - b) <= tolerance;
		}

		template<class T, class U>
		constexpr decltype(auto) Min(const T& a, const U& b) noexcept
		{
			return (a < b) ? a : b;
		}

		template<class T, class U, class... V>
		constexpr decltype(auto) Min(const T& a, const U& b, const V&... args) noexcept
		{
			return Min(a, Min(b, args...));
		}

		template<class T, class U>
		constexpr decltype(auto) Max(const T& a, const U& b) noexcept
		{
			return (a > b) ? a : b;
		}

		template<class T, class U, class... V>
		constexpr decltype(auto) Max(const T& a, const U& b, const V&... args) noexcept
		{
			return Max(a, Max(b, args...));
		}

		template<class T>
		constexpr decltype(auto) Clamp(const T& value, const T& min, const T& max) noexcept
		{
			return value < min ? min : value > max ? max : value;
		}
	}
}
