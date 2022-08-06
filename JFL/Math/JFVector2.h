//
//  File: JFVector2.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFMatrix2;
    class JFVector2 final
    {
    public:
        constexpr JFVector2() noexcept;
        constexpr JFVector2(float x, float y) noexcept;

        constexpr static float Dot(const JFVector2& v1, const JFVector2& v2) noexcept;

        constexpr bool operator==(const JFVector2& v) const noexcept;
        constexpr bool operator!=(const JFVector2& v) const noexcept;

        constexpr JFVector2 operator+(const JFVector2& v) const noexcept;
        constexpr JFVector2 operator-() const noexcept;
        constexpr JFVector2 operator-(const JFVector2& v) const noexcept;
        constexpr JFVector2 operator*(const JFMatrix2& m) const noexcept;
        constexpr JFVector2 operator*(float f) const noexcept;
        constexpr JFVector2 operator/(const JFVector2& v) const noexcept;
        constexpr friend JFVector2 operator*(float f, const JFVector2& v) noexcept;

        constexpr JFVector2& operator+=(const JFVector2& v) noexcept;
        constexpr JFVector2& operator-=(const JFVector2& v) noexcept;
        constexpr JFVector2& operator*=(const JFMatrix2& m) noexcept;
        constexpr JFVector2& operator*=(float f) noexcept;
        constexpr JFVector2& operator/=(const JFVector2& v) noexcept;

        inline float Angle() const noexcept;
        inline float Length() const noexcept;
        constexpr float LengthSq() const noexcept;
        constexpr JFVector2& Normalize() noexcept;

        constexpr bool IsNan() const noexcept;
        constexpr bool IsNearZero(float toleranceSqrt = 1.0e-12f) const noexcept;
        constexpr bool IsNormalized(float tolerance = 1.0e-6f) const noexcept;

    public:
        union
        {
            struct
            {
                float x, y;
            };
            float scalars[2];
        };
    };
}

#include "JFVector2.inl"
