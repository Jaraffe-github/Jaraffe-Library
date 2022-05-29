//
//  File: JFLinearTransform2.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector2.h"
#include "JFMatrix2.h"

namespace JFL
{
    constexpr JFLinearTransform2::JFLinearTransform2() noexcept
        : matrix2()
    {
    }

    constexpr JFLinearTransform2::JFLinearTransform2(const JFMatrix2& m) noexcept
        : matrix2(m)
    {
    }

    constexpr bool JFLinearTransform2::operator==(const JFLinearTransform2& lt) const noexcept
    {
        return matrix2 == lt.matrix2;
    }

    constexpr bool JFLinearTransform2::operator!=(const JFLinearTransform2& lt) const noexcept
    {
        return matrix2 != lt.matrix2;
    }

    constexpr JFLinearTransform2& JFLinearTransform2::Scale(float x, float y) noexcept
    {
        matrix2._11 *= x;
        matrix2._12 *= y;
        matrix2._21 *= x;
        matrix2._22 *= y;
        return *this;
    }

    constexpr JFLinearTransform2& JFLinearTransform2::Scale(const JFVector2& v) noexcept
    {
        matrix2._11 *= v.x;
        matrix2._12 *= v.y;
        matrix2._21 *= v.x;
        matrix2._22 *= v.y;
        return *this;
    }

    inline JFLinearTransform2& JFLinearTransform2::Rotate(float angle) noexcept
    {
        float cos = std::cosf(angle);
        float sin = std::sinf(angle);
        matrix2 *= JFMatrix2{ cos, sin, -sin, cos };
        return *this;
    }

    constexpr JFLinearTransform2& JFLinearTransform2::Multiply(const JFMatrix2& m) noexcept
    {
        matrix2 *= m;
        return *this;
    }

    constexpr JFMatrix2& JFLinearTransform2::Matrix2() noexcept
    { 
        return matrix2; 
    }

    constexpr const JFMatrix2& JFLinearTransform2::Matrix2() const noexcept
    {
        return matrix2;
    }
}