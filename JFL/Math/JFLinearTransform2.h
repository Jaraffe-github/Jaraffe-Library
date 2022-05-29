//
//  File: JFLinearTransform2.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFMatrix2.h"

namespace JFL
{
    class JFVector2;
    class JFLinearTransform2 final
    {
    public:
        constexpr JFLinearTransform2() noexcept;
        constexpr JFLinearTransform2(const JFMatrix2& m) noexcept;

        constexpr bool operator == (const JFLinearTransform2& lt) const noexcept;
        constexpr bool operator != (const JFLinearTransform2& lt) const noexcept;

        constexpr JFLinearTransform2& Scale(float x, float y) noexcept;
        constexpr JFLinearTransform2& Scale(const JFVector2& v) noexcept;
        inline JFLinearTransform2& Rotate(float angle) noexcept;
        constexpr JFLinearTransform2& Multiply(const JFMatrix2& m) noexcept;

        constexpr JFMatrix2& Matrix2() noexcept;
        constexpr const JFMatrix2& Matrix2() const noexcept;

    public:
        JFMatrix2 matrix2;
    };
}

#include "JFLinearTransform2.inl"