//
//  File: JFVector4.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFMatrix4;
    class JFVector4 final
    {
    public:
        constexpr JFVector4() noexcept;
        constexpr JFVector4(float x, float y, float z, float w) noexcept;

        constexpr static float Dot(const JFVector4& v1, const JFVector4& v2) noexcept;

        constexpr bool operator==(const JFVector4& v) const noexcept;
        constexpr bool operator!=(const JFVector4& v) const noexcept;

        constexpr JFVector4 operator+(const JFVector4& v) const noexcept;
        constexpr JFVector4 operator-() const noexcept;
        constexpr JFVector4 operator-(const JFVector4& v) const noexcept;
        constexpr JFVector4 operator*(const JFMatrix4& m) const noexcept;
        constexpr JFVector4 operator*(float f) const noexcept;
        constexpr JFVector4 operator/(const JFVector4& v) const noexcept;
        constexpr friend JFVector4 operator*(float f, const JFVector4& v) noexcept;

        constexpr JFVector4& operator+=(const JFVector4& v) noexcept;
        constexpr JFVector4& operator-=(const JFVector4& v) noexcept;
        constexpr JFVector4& operator*=(const JFMatrix4& m) noexcept;
        constexpr JFVector4& operator*=(float f) noexcept;
        constexpr JFVector4& operator/=(const JFVector4& v) noexcept;

        inline float Length() const noexcept;
        constexpr float LengthSq() const noexcept;
        constexpr JFVector4& Normalize() noexcept;

        constexpr bool IsNan() const noexcept;
        constexpr bool IsNearZero(float toleranceSqrt = 1.0e-12f) const noexcept;
        constexpr bool IsNormalized(float tolerance = 1.0e-6f) const noexcept;

    public:
        union
        {
            struct
            {
                float x, y, z, w;
            };
            float value[4];
        };
    };
}

#include "JFVector4.inl"
