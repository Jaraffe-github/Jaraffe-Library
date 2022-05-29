//
//  File: JFVector3.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFMatrix3;
    class JFVector3 final
    {
    public:
        constexpr JFVector3() noexcept;
        constexpr JFVector3(float x, float y, float z) noexcept;

        constexpr static float Dot(const JFVector3& v1, const JFVector3& v2) noexcept;
        constexpr static JFVector3 Cross(const JFVector3& v1, const JFVector3& v2) noexcept;

        constexpr bool operator==(const JFVector3& v) const noexcept;
		constexpr bool operator!=(const JFVector3& v) const noexcept;

		constexpr JFVector3 operator+(const JFVector3& v) const noexcept;
		constexpr JFVector3 operator-() const noexcept;
		constexpr JFVector3 operator-(const JFVector3& v) const noexcept;
		constexpr JFVector3 operator*(const JFMatrix3& m) const noexcept;
		constexpr JFVector3 operator*(float f) const noexcept;
		constexpr JFVector3 operator/(const JFVector3& v) const noexcept;
		constexpr friend JFVector3 operator*(float f, const JFVector3& v) noexcept;

		constexpr JFVector3& operator+=(const JFVector3& v) noexcept;
		constexpr JFVector3& operator-=(const JFVector3& v) noexcept;
		constexpr JFVector3& operator*=(const JFMatrix3& m) noexcept;
		constexpr JFVector3& operator*=(float f) noexcept;
		constexpr JFVector3& operator/=(const JFVector3& v) noexcept;

		inline float Length() const noexcept;
		constexpr float LengthSq() const noexcept;
		constexpr JFVector3& Normalize() noexcept;

        constexpr bool IsNan() const noexcept;
        constexpr bool IsNearZero(float toleranceSqrt = 1.0e-12f) const noexcept;
        constexpr bool IsNormalized(float tolerance = 1.0e-6f) const noexcept;

    public:
        union
        {
            struct
            {
                float x, y, z;
            };
            float value[3];
        };
    };
}

#include "JFVector3.inl"
