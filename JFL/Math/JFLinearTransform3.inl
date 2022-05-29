//
//  File: JFLinearTransform3.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector3.h"
#include "JFMatrix3.h"

namespace JFL
{
    constexpr JFLinearTransform3::JFLinearTransform3() noexcept
        : matrix3()
    {
    }

    constexpr JFLinearTransform3::JFLinearTransform3(const JFMatrix3& m) noexcept
        : matrix3(m)
    {
    }

    constexpr bool JFLinearTransform3::operator==(const JFLinearTransform3& lt) const noexcept
    {
        return matrix3 == lt.matrix3;
    }

    constexpr bool JFLinearTransform3::operator!=(const JFLinearTransform3& lt) const noexcept
    {
        return matrix3 != lt.matrix3;
    }

    constexpr JFLinearTransform3& JFLinearTransform3::Scale(float x, float y, float z) noexcept
    {
        matrix3._11 *= x;
        matrix3._12 *= y;
        matrix3._13 *= z;
        matrix3._21 *= x;
        matrix3._22 *= y;
        matrix3._23 *= z;
        matrix3._31 *= x;
        matrix3._32 *= y;
        matrix3._33 *= z;
        return *this;
    }

    constexpr JFLinearTransform3& JFLinearTransform3::Scale(const JFVector3& v) noexcept
    {
        matrix3._11 *= v.x;
        matrix3._12 *= v.y;
        matrix3._13 *= v.z;
        matrix3._21 *= v.x;
        matrix3._22 *= v.y;
        matrix3._23 *= v.z;
        matrix3._31 *= v.x;
        matrix3._32 *= v.y;
        matrix3._33 *= v.z;
        return *this;
    }

    inline JFLinearTransform3& JFLinearTransform3::RotateX(float angle) noexcept
    {
        float cos = std::cosf(angle);
        float sin = std::sinf(angle);
        matrix3 *= JFMatrix3(1.f, 0.f, 0.f,
                             0.f, cos, -sin,
                             0.f, sin, cos);
        return *this;

    }

    inline JFLinearTransform3& JFLinearTransform3::RotateY(float angle) noexcept
    {
        float cos = std::cosf(angle);
        float sin = std::sinf(angle);
        matrix3 *= JFMatrix3{ cos, 0.f, sin,
                              0.f, 1.f, 0.f,
                              -sin, 0.f, cos };
        return *this;
    }

    inline JFLinearTransform3& JFLinearTransform3::RotateZ(float angle) noexcept
    {
        float cos = std::cosf(angle);
        float sin = std::sinf(angle);
        matrix3 *= JFMatrix3{ cos, -sin, 0.f,
                              sin, cos, 0.f,
                              0.f, 0.f, 1.f };
        return *this;
    }

    inline JFLinearTransform3& JFLinearTransform3::Rotate(const JFVector3& axis, float angle) noexcept
    {
        float cos = std::cosf(angle);
        float sin = std::sinf(angle);
        float revCos = 1.f - cos;
        matrix3 *= JFMatrix3{ cos + revCos * (axis.x * axis.x),
                              revCos * (axis.x * axis.y) + (sin * axis.z),
                              revCos * (axis.x * axis.z) - (sin * axis.y),
                              revCos * (axis.x * axis.y) - (sin * axis.z),
                              cos + revCos * (axis.y * axis.y),
                              revCos * (axis.y * axis.z) + (sin * axis.x),
                              revCos * (axis.x * axis.z) + (sin * axis.y),
                              revCos * (axis.y * axis.z) - (sin * axis.x),
                              cos + revCos * (axis.z * axis.z) };
        return *this;
    }

    constexpr JFLinearTransform3& JFLinearTransform3::Multiply(const JFMatrix3& m) noexcept
    {
        matrix3 *= m;
        return *this;
    }

    constexpr JFMatrix3& JFLinearTransform3::Matrix3() noexcept 
    {
        return matrix3; 
    }

    constexpr const JFMatrix3& JFLinearTransform3::Matrix3() const noexcept 
    { 
        return matrix3; 
    }
}