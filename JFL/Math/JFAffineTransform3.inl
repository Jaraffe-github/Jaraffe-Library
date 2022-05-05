//
//  File: JFAffineTransform3.inl
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector3.h"
#include "JFMatrix4.h"
#include "JFLinearTransform3.h"

namespace JFL
{
    constexpr JFAffineTransform3::JFAffineTransform3() noexcept
        : matrix3()
        , translation()
    {
    }

    constexpr JFAffineTransform3::JFAffineTransform3(const JFMatrix4& m) noexcept
        : matrix3(m._11, m._12, m._13,
                  m._21, m._22, m._23,
                  m._31, m._32, m._33)
        , translation(m._41, m._42, m._43)
    {
    }

    constexpr bool JFAffineTransform3::operator==(const JFAffineTransform3& at) const noexcept
    {
        return translation == at.translation && matrix3 == at.matrix3;
    }

    constexpr bool JFAffineTransform3::operator!=(const JFAffineTransform3& at) const noexcept
    {
        return translation != at.translation || matrix3 != at.matrix3;;
    }

    constexpr JFAffineTransform3& JFAffineTransform3::Translate(float x, float y, float z) noexcept
    {
        translation.x += x;
        translation.y += y;
        translation.z += z;
        return *this;
    }

    constexpr JFAffineTransform3& JFAffineTransform3::Translate(const JFVector3& v) noexcept
    {
        translation.x += v.x;
        translation.y += v.y;
        translation.z += v.z;
        return *this;
    }

    constexpr JFAffineTransform3& JFAffineTransform3::Multiply(const JFLinearTransform3& lt) noexcept
    {
        translation *= lt.matrix3;
        matrix3 *= lt.matrix3;
        return *this;
    }

    constexpr JFAffineTransform3& JFAffineTransform3::Multiply(const JFAffineTransform3& at) noexcept
    {
        translation = translation * at.matrix3 + at.translation;
        matrix3 *= at.matrix3;
        return *this;
    }

    constexpr JFMatrix4 JFAffineTransform3::Matrix4() const noexcept
    {
        return { matrix3._11, matrix3._12, matrix3._13, 0.f
               , matrix3._21, matrix3._22, matrix3._23, 0.f
               , matrix3._31, matrix3._32, matrix3._33, 0.f
               , translation.x, translation.y, translation.z, 1.f };
    }

    constexpr const JFMatrix3& JFAffineTransform3::Matrix3() const noexcept
    { 
        return matrix3; 
    }
}