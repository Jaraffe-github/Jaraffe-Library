//
//  File: JFMatrix4.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector4.h"

namespace JFL
{
    constexpr JFMatrix4::JFMatrix4() noexcept
        : _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
        , _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
        , _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
        , _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
    {
    }

	constexpr JFMatrix4::JFMatrix4(const JFVector4& row1,
								   const JFVector4& row2,
								   const JFVector4& row3,
								   const JFVector4& row4) noexcept
		: _11(row1.x), _12(row1.y), _13(row1.z), _14(row1.w)
		, _21(row2.x), _22(row2.y), _23(row2.z), _24(row2.w)
		, _31(row3.x), _32(row3.y), _33(row3.z), _34(row3.w)
		, _41(row4.x), _42(row4.y), _43(row4.z), _44(row4.w)
	{
	}

	constexpr JFMatrix4::JFMatrix4(float m11, float m12, float m13, float m14,
                                   float m21, float m22, float m23, float m24,
                                   float m31, float m32, float m33, float m34,
                                   float m41, float m42, float m43, float m44) noexcept
        : _11(m11), _12(m12), _13(m13), _14(m14)
        , _21(m21), _22(m22), _23(m23), _24(m24)
        , _31(m31), _32(m32), _33(m33), _34(m34)
        , _41(m41), _42(m42), _43(m43), _44(m44)
    {
    }

    constexpr bool JFMatrix4::operator==(const JFMatrix4& m) const noexcept
    {
        return _11 == m._11 && _12 == m._12 && _13 == m._13 && _14 == m._14
            && _21 == m._21 && _22 == m._22 && _23 == m._23 && _24 == m._24
            && _31 == m._31 && _32 == m._32 && _33 == m._33 && _34 == m._34
            && _41 == m._41 && _42 == m._42 && _43 == m._43 && _44 == m._44;
    }

    constexpr bool JFMatrix4::operator!=(const JFMatrix4& m) const noexcept
    {
        return _11 != m._11 || _12 != m._12 || _13 != m._13 || _14 != m._14
            || _21 != m._21 || _22 != m._22 || _23 != m._23 || _24 != m._24
            || _31 != m._31 || _32 != m._32 || _33 != m._33 || _34 != m._34
            || _41 != m._41 || _42 != m._42 || _43 != m._43 || _44 != m._44;
    }

    constexpr JFMatrix4 JFMatrix4::operator+(const JFMatrix4& m) const noexcept
    {
        return { _11 + m._11, _12 + m._12, _13 + m._13, _14 + m._14
               , _21 + m._21, _22 + m._22, _23 + m._23, _24 + m._24
               , _31 + m._31, _32 + m._32, _33 + m._33, _34 + m._34
               , _41 + m._41, _42 + m._42, _43 + m._43, _44 + m._44 };
    }

    constexpr JFMatrix4 JFMatrix4::operator-(const JFMatrix4& m) const noexcept
    {
        return { _11 - m._11, _12 - m._12, _13 - m._13, _14 - m._14
               , _21 - m._21, _22 - m._22, _23 - m._23, _24 - m._24
               , _31 - m._31, _32 - m._32, _33 - m._33, _34 - m._34
               , _41 - m._41, _42 - m._42, _43 - m._43, _44 - m._44 };
    }

    constexpr JFMatrix4 JFMatrix4::operator*(const JFMatrix4& m) const noexcept
    {
        JFMatrix4 mat;
        mat._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31) + (_14 * m._41);
        mat._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32) + (_14 * m._42);
        mat._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33) + (_14 * m._43);
        mat._14 = (_11 * m._14) + (_12 * m._24) + (_13 * m._34) + (_14 * m._44);
        mat._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31) + (_24 * m._41);
        mat._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32) + (_24 * m._42);
        mat._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33) + (_24 * m._43);
        mat._24 = (_21 * m._14) + (_22 * m._24) + (_23 * m._34) + (_24 * m._44);
        mat._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31) + (_34 * m._41);
        mat._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32) + (_34 * m._42);
        mat._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33) + (_34 * m._43);
        mat._34 = (_31 * m._14) + (_32 * m._24) + (_33 * m._34) + (_34 * m._44);
        mat._41 = (_41 * m._11) + (_42 * m._21) + (_43 * m._31) + (_44 * m._41);
        mat._42 = (_41 * m._12) + (_42 * m._22) + (_43 * m._32) + (_44 * m._42);
        mat._43 = (_41 * m._13) + (_42 * m._23) + (_43 * m._33) + (_44 * m._43);
        mat._44 = (_41 * m._14) + (_42 * m._24) + (_43 * m._34) + (_44 * m._44);
        return mat;
    }

    constexpr JFMatrix4 JFMatrix4::operator*(float f) const noexcept
    {
        return { (_11 * f), (_12 * f), (_13 * f), (_14 * f)
               , (_21 * f), (_22 * f), (_23 * f), (_24 * f)
               , (_31 * f), (_32 * f), (_33 * f), (_34 * f)
               , (_41 * f), (_42 * f), (_43 * f), (_44 * f) };
    }

    constexpr JFMatrix4& JFMatrix4::operator+=(const JFMatrix4& m) noexcept
    {
        _11 += m._11; _12 += m._12; _13 += m._13; _14 += m._14;
        _21 += m._21; _22 += m._22; _23 += m._23; _24 += m._24;
        _31 += m._31; _32 += m._32; _33 += m._33; _34 += m._34;
        _41 += m._41; _42 += m._42; _43 += m._43; _44 += m._44;
        return *this;
    }

    constexpr JFMatrix4& JFMatrix4::operator-=(const JFMatrix4& m) noexcept
    {
        _11 -= m._11; _12 -= m._12; _13 -= m._13; _14 -= m._14;
        _21 -= m._21; _22 -= m._22; _23 -= m._23; _24 -= m._24;
        _31 -= m._31; _32 -= m._32; _33 -= m._33; _34 -= m._34;
        _41 -= m._41; _42 -= m._42; _43 -= m._43; _44 -= m._44;
        return *this;
    }

    constexpr JFMatrix4& JFMatrix4::operator*=(const JFMatrix4& m) noexcept
    {
        JFMatrix4 mat{ *this };
        _11 = (mat._11 * m._11) + (mat._12 * m._21) + (mat._13 * m._31) + (mat._14 * m._41);
        _12 = (mat._11 * m._12) + (mat._12 * m._22) + (mat._13 * m._32) + (mat._14 * m._42);
        _13 = (mat._11 * m._13) + (mat._12 * m._23) + (mat._13 * m._33) + (mat._14 * m._43);
        _14 = (mat._11 * m._14) + (mat._12 * m._24) + (mat._13 * m._34) + (mat._14 * m._44);
        _21 = (mat._21 * m._11) + (mat._22 * m._21) + (mat._23 * m._31) + (mat._24 * m._41);
        _22 = (mat._21 * m._12) + (mat._22 * m._22) + (mat._23 * m._32) + (mat._24 * m._42);
        _23 = (mat._21 * m._13) + (mat._22 * m._23) + (mat._23 * m._33) + (mat._24 * m._43);
        _24 = (mat._21 * m._14) + (mat._22 * m._24) + (mat._23 * m._34) + (mat._24 * m._44);
        _31 = (mat._31 * m._11) + (mat._32 * m._21) + (mat._33 * m._31) + (mat._34 * m._41);
        _32 = (mat._31 * m._12) + (mat._32 * m._22) + (mat._33 * m._32) + (mat._34 * m._42);
        _33 = (mat._31 * m._13) + (mat._32 * m._23) + (mat._33 * m._33) + (mat._34 * m._43);
        _34 = (mat._31 * m._14) + (mat._32 * m._24) + (mat._33 * m._34) + (mat._34 * m._44);
        _41 = (mat._41 * m._11) + (mat._42 * m._21) + (mat._43 * m._31) + (mat._44 * m._41);
        _42 = (mat._41 * m._12) + (mat._42 * m._22) + (mat._43 * m._32) + (mat._44 * m._42);
        _43 = (mat._41 * m._13) + (mat._42 * m._23) + (mat._43 * m._33) + (mat._44 * m._43);
        _44 = (mat._41 * m._14) + (mat._42 * m._24) + (mat._43 * m._34) + (mat._44 * m._44);
        return *this;
    }

    constexpr JFMatrix4& JFMatrix4::operator*=(float f) noexcept
    {
        _11 *= f; _12 *= f; _13 *= f; _14 *= f;
        _21 *= f; _22 *= f; _23 *= f; _24 *= f;
        _31 *= f; _32 *= f; _33 *= f; _34 *= f;
        _41 *= f; _42 *= f; _43 *= f; _44 *= f;
        return *this;
    }

    constexpr JFMatrix4 JFMatrix4::TransposeMatrix() const noexcept
    {
        return { _11, _21, _31, _41
               , _12, _22, _32, _42
               , _13, _23, _33, _43
               , _14, _24, _34, _44 };
    }

    constexpr JFMatrix4 JFMatrix4::InverseMatrix() const noexcept
    {
        // invertible matrix
        if (float determinant = Determinant(); determinant != 0.0f)
        {
            // adjoint matrix / determinant
            float detInv = 1.0f / determinant;

            JFMatrix4 mat;
            mat._11 = ((_23 * _34 * _42) - (_24 * _33 * _42) + (_24 * _32 * _43) - (_22 * _34 * _43) - (_23 * _32 * _44) + (_22 * _33 * _44)) * detInv;
            mat._12 = ((_14 * _33 * _42) - (_13 * _34 * _42) - (_14 * _32 * _43) + (_12 * _34 * _43) + (_13 * _32 * _44) - (_12 * _33 * _44)) * detInv;
            mat._13 = ((_13 * _24 * _42) - (_14 * _23 * _42) + (_14 * _22 * _43) - (_12 * _24 * _43) - (_13 * _22 * _44) + (_12 * _23 * _44)) * detInv;
            mat._14 = ((_14 * _23 * _32) - (_13 * _24 * _32) - (_14 * _22 * _33) + (_12 * _24 * _33) + (_13 * _22 * _34) - (_12 * _23 * _34)) * detInv;
            mat._21 = ((_24 * _33 * _41) - (_23 * _34 * _41) - (_24 * _31 * _43) + (_21 * _34 * _43) + (_23 * _31 * _44) - (_21 * _33 * _44)) * detInv;
            mat._22 = ((_13 * _34 * _41) - (_14 * _33 * _41) + (_14 * _31 * _43) - (_11 * _34 * _43) - (_13 * _31 * _44) + (_11 * _33 * _44)) * detInv;
            mat._23 = ((_14 * _23 * _41) - (_13 * _24 * _41) - (_14 * _21 * _43) + (_11 * _24 * _43) + (_13 * _21 * _44) - (_11 * _23 * _44)) * detInv;
            mat._24 = ((_13 * _24 * _31) - (_14 * _23 * _31) + (_14 * _21 * _33) - (_11 * _24 * _33) - (_13 * _21 * _34) + (_11 * _23 * _34)) * detInv;
            mat._31 = ((_22 * _34 * _41) - (_24 * _32 * _41) + (_24 * _31 * _42) - (_21 * _34 * _42) - (_22 * _31 * _44) + (_21 * _32 * _44)) * detInv;
            mat._32 = ((_14 * _32 * _41) - (_12 * _34 * _41) - (_14 * _31 * _42) + (_11 * _34 * _42) + (_12 * _31 * _44) - (_11 * _32 * _44)) * detInv;
            mat._33 = ((_12 * _24 * _41) - (_14 * _22 * _41) + (_14 * _21 * _42) - (_11 * _24 * _42) - (_12 * _21 * _44) + (_11 * _22 * _44)) * detInv;
            mat._34 = ((_14 * _22 * _31) - (_12 * _24 * _31) - (_14 * _21 * _32) + (_11 * _24 * _32) + (_12 * _21 * _34) - (_11 * _22 * _34)) * detInv;
            mat._41 = ((_23 * _32 * _41) - (_22 * _33 * _41) - (_23 * _31 * _42) + (_21 * _33 * _42) + (_22 * _31 * _43) - (_21 * _32 * _43)) * detInv;
            mat._42 = ((_12 * _33 * _41) - (_13 * _32 * _41) + (_13 * _31 * _42) - (_11 * _33 * _42) - (_12 * _31 * _43) + (_11 * _32 * _43)) * detInv;
            mat._43 = ((_13 * _22 * _41) - (_12 * _23 * _41) - (_13 * _21 * _42) + (_11 * _23 * _42) + (_12 * _21 * _43) - (_11 * _22 * _43)) * detInv;
            mat._44 = ((_12 * _23 * _31) - (_13 * _22 * _31) + (_13 * _21 * _32) - (_11 * _23 * _32) - (_12 * _21 * _33) + (_11 * _22 * _33)) * detInv;
            return mat;
        }
        // singular matrix
        else
        {
            return {};
        }
    }

    constexpr float JFMatrix4::Determinant() const noexcept
    {
        return
            (_14 * _23 * _32 * _41) - (_13 * _24 * _32 * _41) - (_14 * _22 * _33 * _41) + (_12 * _24 * _33 * _41) + (_13 * _22 * _34 * _41) - (_12 * _23 * _34 * _41) -
            (_14 * _23 * _31 * _42) + (_13 * _24 * _31 * _42) + (_14 * _21 * _33 * _42) - (_11 * _24 * _33 * _42) - (_13 * _21 * _34 * _42) + (_11 * _23 * _34 * _42) +
            (_14 * _22 * _31 * _43) - (_12 * _24 * _31 * _43) - (_14 * _21 * _32 * _43) + (_11 * _24 * _32 * _43) + (_12 * _21 * _34 * _43) - (_11 * _22 * _34 * _43) -
            (_13 * _22 * _31 * _44) + (_12 * _23 * _31 * _44) + (_13 * _21 * _32 * _44) - (_11 * _23 * _32 * _44) - (_12 * _21 * _33 * _44) + (_11 * _22 * _33 * _44);
    }

    constexpr JFVector4 JFMatrix4::Row1() const noexcept
    {
        return JFVector4(scalars[0], scalars[1], scalars[2], scalars[3]);
    }

    constexpr JFVector4 JFMatrix4::Row2() const noexcept
    {
        return JFVector4(scalars[4], scalars[5], scalars[6], scalars[7]);
    }

    constexpr JFVector4 JFMatrix4::Row3() const noexcept
    {
        return JFVector4(scalars[8], scalars[9], scalars[10], scalars[11]);
    }

    constexpr JFVector4 JFMatrix4::Row4() const noexcept
    {
        return JFVector4(scalars[12], scalars[13], scalars[14], scalars[15]);
    }
}
