//
//  File: JFAffineTransform2.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFMatrix2.h"
#include "JFVector2.h"

namespace JFL
{
    class JFMatrix3;
    class JFLinearTransform2;
    class JFAffineTransform2 final
    {
    public:
        constexpr JFAffineTransform2() noexcept;
        constexpr JFAffineTransform2(const JFMatrix3& m) noexcept;

        constexpr bool operator == (const JFAffineTransform2& at) const noexcept;
        constexpr bool operator != (const JFAffineTransform2& at) const noexcept;

        constexpr JFAffineTransform2& Translate(float x, float y) noexcept;
        constexpr JFAffineTransform2& Translate(const JFVector2& v) noexcept;
        constexpr JFAffineTransform2& Multiply(const JFLinearTransform2& lt) noexcept;
        constexpr JFAffineTransform2& Multiply(const JFAffineTransform2& at) noexcept;

        constexpr JFMatrix3 Matrix3() const noexcept;
        constexpr const JFMatrix2& Matrix2() const noexcept;

    public:
        JFMatrix2 matrix2;
        JFVector2 translation;
    };
}

#include "JFAffineTransform2.inl"