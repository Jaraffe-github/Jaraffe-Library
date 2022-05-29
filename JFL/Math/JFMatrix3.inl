//
//  File: JFMatrix3.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector3.h"

namespace JFL
{
    constexpr JFMatrix3::JFMatrix3() noexcept
        : _11(1.0f), _12(0.0f), _13(0.0f)
        , _21(0.0f), _22(1.0f), _23(0.0f)
        , _31(0.0f), _32(0.0f), _33(1.0f)
    {
    }

    constexpr JFMatrix3::JFMatrix3(const JFVector3& row1, 
                                   const JFVector3& row2, 
                                   const JFVector3& row3) noexcept
        : _11(row1.x), _12(row1.y), _13(row1.z)
        , _21(row2.x), _22(row2.y), _23(row2.z)
        , _31(row3.x), _32(row3.y), _33(row3.z)
    {
    }

    constexpr JFMatrix3::JFMatrix3(float m11, float m12, float m13,
                                   float m21, float m22, float m23,
                                   float m31, float m32, float m33) noexcept
        : _11(m11), _12(m12), _13(m13)
        , _21(m21), _22(m22), _23(m23)
        , _31(m31), _32(m32), _33(m33)
    {
    }

    constexpr bool JFMatrix3::operator==(const JFMatrix3& m) const noexcept
    {
        return _11 == m._11 && _12 == m._12 && _13 == m._13
            && _21 == m._21 && _22 == m._22 && _23 == m._23
            && _31 == m._31 && _32 == m._32 && _33 == m._33;
    }

    constexpr bool JFMatrix3::operator!=(const JFMatrix3& m) const noexcept
    {
        return _11 != m._11 || _12 != m._12 || _13 != m._13
            || _21 != m._21 || _22 != m._22 || _23 != m._23
            || _31 != m._31 || _32 != m._32 || _33 != m._33;
    }

    constexpr JFMatrix3 JFMatrix3::operator+(const JFMatrix3& m) const noexcept
    {
        return { _11 + m._11, _12 + m._12, _13 + m._13
               , _21 + m._21, _22 + m._22, _23 + m._23
               , _31 + m._31, _32 + m._32, _33 + m._33 };
    }

    constexpr JFMatrix3 JFMatrix3::operator-(const JFMatrix3& m) const noexcept
    {
        return { _11 - m._11, _12 - m._12, _13 - m._13
               , _21 - m._21, _22 - m._22, _23 - m._23
               , _31 - m._31, _32 - m._32, _33 - m._33 };
    }

    constexpr JFMatrix3 JFMatrix3::operator*(const JFMatrix3& m) const noexcept
    {
        JFMatrix3 mat;
        mat._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31);
        mat._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32);
        mat._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33);
        mat._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31);
        mat._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32);
        mat._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33);
        mat._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31);
        mat._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32);
        mat._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33);
        return mat;
    }

    constexpr JFMatrix3 JFMatrix3::operator*(float f) const noexcept
    {
        return { (_11 * f), (_12 * f), (_13 * f)
               , (_21 * f), (_22 * f), (_23 * f)
               , (_31 * f), (_32 * f), (_33 * f) };
    }

    constexpr JFMatrix3& JFMatrix3::operator+=(const JFMatrix3& m) noexcept
    {
        _11 += m._11;
        _12 += m._12;
        _13 += m._13;
        _21 += m._21;
        _22 += m._22;
        _23 += m._23;
        _31 += m._31;
        _32 += m._32;
        _33 += m._33;
        return *this;
    }

    constexpr JFMatrix3& JFMatrix3::operator-=(const JFMatrix3& m) noexcept
    {
        _11 -= m._11;
        _12 -= m._12;
        _13 -= m._13;
        _21 -= m._21;
        _22 -= m._22;
        _23 -= m._23;
        _31 -= m._31;
        _32 -= m._32;
        _33 -= m._33;
        return *this;
    }

    constexpr JFMatrix3& JFMatrix3::operator*=(const JFMatrix3& m) noexcept
    {
        JFMatrix3 mat{ *this };
        _11 = (mat._11 * m._11) + (mat._12 * m._21) + (mat._13 * m._31);
        _12 = (mat._11 * m._12) + (mat._12 * m._22) + (mat._13 * m._32);
        _13 = (mat._11 * m._13) + (mat._12 * m._23) + (mat._13 * m._33);
        _21 = (mat._21 * m._11) + (mat._22 * m._21) + (mat._23 * m._31);
        _22 = (mat._21 * m._12) + (mat._22 * m._22) + (mat._23 * m._32);
        _23 = (mat._21 * m._13) + (mat._22 * m._23) + (mat._23 * m._33);
        _31 = (mat._31 * m._11) + (mat._32 * m._21) + (mat._33 * m._31);
        _32 = (mat._31 * m._12) + (mat._32 * m._22) + (mat._33 * m._32);
        _33 = (mat._31 * m._13) + (mat._32 * m._23) + (mat._33 * m._33);
        return *this;
    }

    constexpr JFMatrix3& JFMatrix3::operator*=(float f) noexcept
    {
        _11 *= f; _12 *= f; _13 *= f;
        _21 *= f; _22 *= f; _23 *= f;
        _31 *= f; _32 *= f; _33 *= f;
        return *this;
    }

    constexpr JFMatrix3 JFMatrix3::TransposeMatrix() const noexcept
    {
        return { _11, _21, _31
               , _12, _22, _32
               , _13, _23, _33 };
    }

    constexpr JFMatrix3 JFMatrix3::InverseMatrix() const noexcept
    {
        // invertible matrix
        if (float determinant = Determinant(); determinant != 0.0f)
        {
            // adjoint matrix / determinant
            float detInv = 1.0f / determinant;

            JFMatrix3 mat;
            mat._11 = (_22 * _33 - _32 * _23) * detInv;
            mat._12 = (_32 * _13 - _12 * _33) * detInv;
            mat._13 = (_12 * _23 - _22 * _13) * detInv;
            mat._21 = (_31 * _23 - _21 * _33) * detInv;
            mat._22 = (_11 * _33 - _31 * _13) * detInv;
            mat._23 = (_21 * _13 - _11 * _23) * detInv;
            mat._31 = (_21 * _32 - _31 * _22) * detInv;
            mat._32 = (_31 * _12 - _11 * _32) * detInv;
            mat._33 = (_11 * _22 - _21 * _12) * detInv;
            return mat;
        }
        // singular matrix
        else
        {
            return {};
        }
    }

    constexpr float JFMatrix3::Determinant() const noexcept
    {
		return (_11 * _22 * _33) +
			   (_21 * _32 * _13) +
			   (_31 * _12 * _23) -
			   (_31 * _22 * _13) -
			   (_21 * _12 * _33) -
			   (_11 * _32 * _23);
	}
}