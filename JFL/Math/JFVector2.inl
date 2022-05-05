//
//  File: JFVector2.inl
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFMatrix2.h"

namespace JFL
{
    constexpr JFVector2::JFVector2() noexcept
        : x(0.0f), y(0.0f)
    {
    }

    constexpr JFVector2::JFVector2(float x, float y) noexcept
        : x(x), y(y)
    {
    }

    constexpr float JFVector2::Dot(const JFVector2& v1, const JFVector2& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    constexpr bool JFVector2::operator==(const JFVector2& v) const noexcept
    {
        return x == v.x && y == v.y;
    }

    constexpr bool JFVector2::operator!=(const JFVector2& v) const noexcept
    {
        return x != v.x || y != v.y;
    }

    constexpr JFVector2 JFVector2::operator-() const noexcept
    {
        return { -x, -y };
    }

    constexpr JFVector2 JFVector2::operator+(const JFVector2& v) const noexcept
    {                                      
        return { x + v.x, y + v.y };       
    }                                      
                                           
    constexpr JFVector2 JFVector2::operator-(const JFVector2& v) const noexcept
    {                                      
        return { x - v.x, y - v.y };       
    }                                      
                                           
    constexpr JFVector2 JFVector2::operator*(const JFMatrix2& m) const noexcept
    {
        return { (x * m._11 + y * m._21)
               , (x * m._12 + y * m._22) };
    }

    constexpr JFVector2 JFVector2::operator*(float f) const noexcept
    {
        return { x * f, y * f };
    }

    constexpr JFVector2 JFVector2::operator/(const JFVector2& v) const noexcept
    {
        return { x / v.x, y / v.y };
    }

    constexpr JFVector2& JFVector2::operator+=(const JFVector2& v) noexcept
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr JFVector2& JFVector2::operator-=(const JFVector2& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr JFVector2& JFVector2::operator*=(const JFMatrix2& m) noexcept
    {
        JFVector2 v(*this);
        x = v.x * m._11 + v.y * m._21;
        y = v.x * m._12 + v.y * m._22;
        return *this;
    }

    constexpr JFVector2& JFVector2::operator*=(float f) noexcept
    {
        x *= f;
        y *= f;
        return *this;
    }

    constexpr JFVector2& JFVector2::operator/=(const JFVector2& v) noexcept
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    inline float JFVector2::Length() const noexcept
    {
        return std::sqrtf(x * x + y * y);
    }

    constexpr float JFVector2::LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    constexpr JFVector2& JFVector2::Normalize() noexcept
    {
        float lenSq = x * x + y * y;
        if (lenSq > 0.0f)
        {
            float lenInv = 1.0f / std::sqrtf(lenSq);
            x *= lenInv;
            y *= lenInv;
        }
        return *this;
    }

    constexpr JFVector2 operator * (float f, const JFVector2& v) noexcept
    {
        return { v.x * f, v.y * f };
    }

    constexpr bool JFVector2::IsNan() const noexcept
    {
        return !(x == x && y == y);
    }

    constexpr bool JFVector2::IsNearZero(float toleranceSqrt) const noexcept
    {
        return LengthSq() <= toleranceSqrt;
    }

    constexpr bool JFVector2::IsNormalized(float tolerance) const noexcept
    {
        return Abs(LengthSq() - 1.0f) <= tolerance;
    }
}
