//
//  File: JFMatrix2.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector2.h"

namespace JFL
{
    constexpr JFMatrix2::JFMatrix2() noexcept
        : _11(1.0f), _12(0.0f)
        , _21(0.0f), _22(1.0f)
    {
    }

    constexpr JFMatrix2::JFMatrix2(const JFVector2& row1, const JFVector2& row2) noexcept
        : _11(row1.x), _12(row1.y)
        , _21(row2.x), _22(row2.y)
    {
    }

    constexpr JFMatrix2::JFMatrix2(float m11, float m12, float m21, float m22) noexcept
        : _11(m11), _12(m12)
        , _21(m21), _22(m22)
    {
    }

    constexpr bool JFMatrix2::operator==(const JFMatrix2& m) const noexcept
    {
        return _11 == m._11 && _12 == m._12
            && _21 == m._21 && _22 == m._22;
    }

    constexpr bool JFMatrix2::operator!=(const JFMatrix2& m) const noexcept
    {
        return _11 != m._11 || _12 != m._12
            || _21 != m._21 || _22 != m._22;
    }

    constexpr JFMatrix2 JFMatrix2::operator+(const JFMatrix2& m) const noexcept
    {
        return { _11 + m._11, _12 + m._12
               , _21 + m._21, _22 + m._22 };
    }

    constexpr JFMatrix2 JFMatrix2::operator-(const JFMatrix2& m) const noexcept
    {
        return { _11 - m._11, _12 - m._12
               , _21 - m._21, _22 - m._22 };
    }

    constexpr JFMatrix2 JFMatrix2::operator*(const JFMatrix2& m) const noexcept
    {
        return { (_11 * m._11 + _12 * m._21), (_11 * m._12 + _12 * m._22)
               , (_21 * m._11 + _22 * m._21), (_21 * m._12 + _22 * m._22) };
    }

    constexpr JFMatrix2 JFMatrix2::operator*(float f) const noexcept
    {
        return { (_11 * f), (_12 * f)
               , (_21 * f), (_22 * f) };
    }

    constexpr JFMatrix2& JFMatrix2::operator+=(const JFMatrix2& m) noexcept
    {
        _11 += m._11;
        _12 += m._12;
        _21 += m._21;
        _22 += m._22;
        return *this;
    }

    constexpr JFMatrix2& JFMatrix2::operator-=(const JFMatrix2& m) noexcept
    {
        _11 -= m._11;
        _12 -= m._12;
        _21 -= m._21;
        _22 -= m._22;
        return *this;
    }

    constexpr JFMatrix2& JFMatrix2::operator*=(const JFMatrix2& m) noexcept
    {
        JFMatrix2 mat{ *this };
        _11 = (mat._11 * m._11) + (mat._12 * m._21);
        _12 = (mat._11 * m._12) + (mat._12 * m._22);
        _21 = (mat._21 * m._11) + (mat._22 * m._21);
        _22 = (mat._21 * m._12) + (mat._22 * m._22);
        return *this;
    }

    constexpr JFMatrix2& JFMatrix2::operator*=(float f) noexcept
    {
        _11 *= f;
        _12 *= f;
        _21 *= f;
        _22 *= f;
        return *this;
    }

    constexpr JFMatrix2 JFMatrix2::TransposeMatrix() const noexcept
    {
        return { _11, _21
               , _12, _22 };
    }

    constexpr JFMatrix2 JFMatrix2::InverseMatrix() const noexcept
    {
        // invertible matrix
        if (float determinant = Determinant(); determinant != 0.0f)
        {
            // adjoint matrix / determinant
            float detInv = 1.0f / determinant;

            JFMatrix2 mat;
            mat._11 = _22 * detInv;
            mat._12 = -_12 * detInv;
            mat._21 = -_21 * detInv;
            mat._22 = _11 * detInv;
            return mat;
        }
        // singular matrix
        else
        {
            return {};
        }
    }

    constexpr float JFMatrix2::Determinant() const noexcept
    {
        return _11 * _22 - _12 * _21;
    }
}