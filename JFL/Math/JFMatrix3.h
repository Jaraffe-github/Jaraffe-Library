//
//  File: JFMatrix3.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFVector3;
    class JFMatrix3 final
    {
    public:
        constexpr JFMatrix3() noexcept;
        constexpr JFMatrix3(const JFVector3& row1, 
                            const JFVector3& row2, 
                            const JFVector3& row3) noexcept;
        constexpr JFMatrix3(float m11, float m12, float m13,
                            float m21, float m22, float m23,
                            float m31, float m32, float m33) noexcept;

        constexpr bool operator==(const JFMatrix3& m) const noexcept;
        constexpr bool operator!=(const JFMatrix3& m) const noexcept;

        constexpr JFMatrix3 operator+(const JFMatrix3& m) const noexcept;
        constexpr JFMatrix3 operator-(const JFMatrix3& m) const noexcept;
        constexpr JFMatrix3 operator*(const JFMatrix3& m) const noexcept;
        constexpr JFMatrix3 operator*(float f) const noexcept;

        constexpr JFMatrix3& operator+=(const JFMatrix3& m) noexcept;
        constexpr JFMatrix3& operator-=(const JFMatrix3& m) noexcept;
        constexpr JFMatrix3& operator*=(const JFMatrix3& m) noexcept;
        constexpr JFMatrix3& operator*=(float f) noexcept;

        constexpr JFMatrix3 TransposeMatrix() const noexcept;
        constexpr JFMatrix3 InverseMatrix() const noexcept;
        constexpr float Determinant() const noexcept;

    public:
        union
        {
            struct
            {
                float _11, _12, _13;
                float _21, _22, _23;
                float _31, _32, _33;
            };
            struct
            {
                float m[3][3];
            };
            float value[9];
        };
    };
}

#include "JFMatrix3.inl"
