//
//  File: JFAffineTransform2.inl
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector2.h"
#include "JFMatrix3.h"
#include "JFLinearTransform2.h"

namespace JFL
{
    constexpr JFAffineTransform2::JFAffineTransform2() noexcept
        : matrix2()
        , translation()
    {
    }

    constexpr JFAffineTransform2::JFAffineTransform2(const JFMatrix3& m) noexcept
        : matrix2(m._11, m._12,
                  m._21, m._22)
        , translation(m._31, m._32)
    {
    }

    constexpr bool JFAffineTransform2::operator==(const JFAffineTransform2& at) const noexcept
    {
        return translation == at.translation && matrix2 == at.matrix2;
    }

    constexpr bool JFAffineTransform2::operator!=(const JFAffineTransform2& at) const noexcept
    {
        return translation != at.translation || matrix2 != at.matrix2;
    }

    constexpr JFAffineTransform2& JFAffineTransform2::Translate(float x, float y) noexcept
    {
        translation.x += x;
        translation.y += y;
        return *this;
    }

    constexpr JFAffineTransform2& JFAffineTransform2::Translate(const JFVector2& v) noexcept
    {
        translation.x += v.x;
        translation.y += v.y;
        return *this;
    }

    constexpr JFAffineTransform2& JFAffineTransform2::Multiply(const JFLinearTransform2& lt) noexcept
    {
        translation *= lt.matrix2;
        matrix2 *= lt.matrix2;
        return *this;
    }

    constexpr JFAffineTransform2& JFAffineTransform2::Multiply(const JFAffineTransform2& at) noexcept
    {
        // t = v1 * m + v2
        translation = translation * at.matrix2 + at.translation;
        matrix2 *= at.matrix2;
        return *this;
    }

    constexpr JFMatrix3 JFAffineTransform2::Matrix3() const noexcept
    {
        return { matrix2._11, matrix2._12, 0.f
               , matrix2._21, matrix2._22, 0.f
               , translation.x, translation.y, 1.f };
    }

    constexpr const JFMatrix2& JFAffineTransform2::Matrix2() const noexcept
    { 
        return matrix2; 
    }
}