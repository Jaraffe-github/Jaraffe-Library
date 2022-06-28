//
//  File: JFMatrix4.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFVector4;
    class JFMatrix4 final
    {
    public:
        constexpr JFMatrix4() noexcept;
        constexpr JFMatrix4(const JFVector4& row1, 
                            const JFVector4& row2,
                            const JFVector4& row3, 
                            const JFVector4& row4) noexcept;
        constexpr JFMatrix4(float m11, float m12, float m13, float m14,
                            float m21, float m22, float m23, float m24,
                            float m31, float m32, float m33, float m34,
                            float m41, float m42, float m43, float m44) noexcept;

        constexpr bool operator==(const JFMatrix4& m) const noexcept;
        constexpr bool operator!=(const JFMatrix4& m) const noexcept;

        constexpr JFMatrix4 operator+(const JFMatrix4& m) const noexcept;
        constexpr JFMatrix4 operator-(const JFMatrix4& m) const noexcept;
        constexpr JFMatrix4 operator*(const JFMatrix4& m) const noexcept;
        constexpr JFMatrix4 operator*(float f) const noexcept;

        constexpr JFMatrix4& operator+=(const JFMatrix4& m) noexcept;
        constexpr JFMatrix4& operator-=(const JFMatrix4& m) noexcept;
        constexpr JFMatrix4& operator*=(const JFMatrix4& m) noexcept;
        constexpr JFMatrix4& operator*=(float f) noexcept;

        constexpr JFMatrix4 TransposeMatrix() const noexcept;
        constexpr JFMatrix4 InverseMatrix() const noexcept;
        constexpr float Determinant() const noexcept;

        constexpr JFVector4 Row1() const noexcept;
        constexpr JFVector4 Row2() const noexcept;
        constexpr JFVector4 Row3() const noexcept;
        constexpr JFVector4 Row4() const noexcept;

    public:
        union
        {
            struct
            {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };
            struct
            {
                float m[4][4];
            };
            float value[16];
        };
    };
}

#include "JFMatrix4.inl"
