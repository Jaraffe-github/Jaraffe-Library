//
//  File: JFVector3.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFMatrix3.h"
#include "JFVector3.h"

namespace JFL
{
    constexpr JFVector3::JFVector3() noexcept
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    constexpr JFVector3::JFVector3(float x, float y, float z) noexcept
        : x(x), y(y), z(z)
    {
    }

    constexpr float JFVector3::Dot(const JFVector3& v1, const JFVector3& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    constexpr JFVector3 JFVector3::Cross(const JFVector3& v1, const JFVector3& v2) noexcept
    {
        return { v1.y * v2.z - v1.z * v2.y
               , v1.z * v2.x - v1.x * v2.z
               , v1.x * v2.y - v1.y * v2.x };
    }

    constexpr bool JFVector3::operator==(const JFVector3& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr bool JFVector3::operator!=(const JFVector3& v) const noexcept
    {
        return x != v.x || y != v.y || z != v.z;
    }

    constexpr JFVector3 JFVector3::operator+(const JFVector3& v) const noexcept
    {
        return { x + v.x, y + v.y, z + v.z };
    }

    constexpr JFVector3 JFVector3::operator-(const JFVector3& v) const noexcept
    {
        return { x - v.x, y - v.y, z - v.z };
    }

    constexpr JFVector3 JFVector3::operator*(const JFMatrix3& m) const noexcept
    {
        return { x * m._11 + y * m._21 + z * m._31
               , x * m._12 + y * m._22 + z * m._32
               , x * m._13 + y * m._23 + z * m._33 };
    }

    constexpr JFVector3 JFVector3::operator*(float f) const noexcept
    {
        return { x * f, y * f, z * f };
    }

    constexpr JFVector3 JFVector3::operator/(const JFVector3& v) const noexcept
    {
        return { x / v.x, y / v.y, z / v.z };
    }

    constexpr JFVector3 operator*(float f, const JFVector3& v) noexcept
    {
        return { v.x * f, v.y * f, v.z * f };
    }

    constexpr JFVector3& JFVector3::operator+=(const JFVector3& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr JFVector3& JFVector3::operator-=(const JFVector3& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr JFVector3& JFVector3::operator*=(const JFMatrix3& m) noexcept
    {
        JFVector3 v{ *this };
        x = v.x * m._11 + v.y * m._21 + v.z * m._31;
        y = v.x * m._12 + v.y * m._22 + v.z * m._32;
        z = v.x * m._13 + v.y * m._23 + v.z * m._33;
        return *this;
    }

    constexpr JFVector3& JFVector3::operator*=(float f) noexcept
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    constexpr JFVector3& JFVector3::operator/=(const JFVector3& v) noexcept
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    constexpr JFVector3 JFVector3::operator-() const noexcept
    {
        return { -x, -y, -z };
    }

    inline float JFVector3::Length() const noexcept
    {
        return std::sqrtf(x * x + y * y + z * z);
    }

    constexpr float JFVector3::LengthSq() const noexcept
    {
        return x * x + y * y + z * z;
    }

    constexpr JFVector3& JFVector3::Normalize() noexcept
    {
        float lenSq = x * x + y * y + z * z;
        if (lenSq > 0.0f)
        {
            float lenInv = 1.0f / std::sqrtf(lenSq);
            x *= lenInv;
            y *= lenInv;
            z *= lenInv;
        }
        return *this;
    }

    constexpr bool JFVector3::IsNan() const noexcept
    {
        return !(x == x && y == y && z == z);
    }

    constexpr bool JFVector3::IsNearZero(float toleranceSqrt) const noexcept
    {
        return LengthSq() <= toleranceSqrt;
    }

    constexpr bool JFVector3::IsNormalized(float tolerance) const noexcept
    {
        return Abs(LengthSq() - 1.0f) <= tolerance;
    }
}
