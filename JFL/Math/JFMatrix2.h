//
//  File: JFMatrix2.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFVector2;
    class JFMatrix2 final
    {
    public:
        constexpr JFMatrix2() noexcept;
        constexpr JFMatrix2(const JFVector2& row1, const JFVector2& row2) noexcept;
        constexpr JFMatrix2(float m11, float m12, float m21, float m22) noexcept;

        constexpr bool operator==(const JFMatrix2& m) const noexcept;
        constexpr bool operator!=(const JFMatrix2& m) const noexcept;

        constexpr JFMatrix2 operator+(const JFMatrix2& m) const noexcept;
        constexpr JFMatrix2 operator-(const JFMatrix2& m) const noexcept;
        constexpr JFMatrix2 operator*(const JFMatrix2& m) const noexcept;
        constexpr JFMatrix2 operator*(float f) const noexcept;

        constexpr JFMatrix2& operator+=(const JFMatrix2& m) noexcept;
        constexpr JFMatrix2& operator-=(const JFMatrix2& m) noexcept;
        constexpr JFMatrix2& operator*=(const JFMatrix2& m) noexcept;
        constexpr JFMatrix2& operator*=(float f) noexcept;

        constexpr JFMatrix2 TransposeMatrix() const noexcept;
        constexpr JFMatrix2 InverseMatrix() const noexcept;
        constexpr float Determinant() const noexcept;

        constexpr JFVector2 Row1() const noexcept;
        constexpr JFVector2 Row2() const noexcept;

    public:
        union
        {
            struct
            {
                float _11, _12;
                float _21, _22;
            };
            struct
            {
                float m[2][2];
            };
            float scalars[4];
        };
    };
}

#include "JFMatrix2.inl"
