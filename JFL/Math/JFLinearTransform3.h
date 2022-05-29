//
//  File: JFLinearTransform3.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFMatrix3.h"

namespace JFL
{
    class JFVector3;
    class JFLinearTransform3 final
    {
    public:
        constexpr JFLinearTransform3() noexcept;
        constexpr JFLinearTransform3(const JFMatrix3& m) noexcept;

        constexpr bool operator == (const JFLinearTransform3& lt) const noexcept;
        constexpr bool operator != (const JFLinearTransform3& lt) const noexcept;

        constexpr JFLinearTransform3& Scale(float x, float y, float z) noexcept;
        constexpr JFLinearTransform3& Scale(const JFVector3& v) noexcept;
        inline JFLinearTransform3& RotateX(float angle) noexcept;
        inline JFLinearTransform3& RotateY(float angle) noexcept;
        inline JFLinearTransform3& RotateZ(float angle) noexcept;
        inline JFLinearTransform3& Rotate(const JFVector3& axis, float angle) noexcept;
        constexpr JFLinearTransform3& Multiply(const JFMatrix3& m) noexcept;

        constexpr JFMatrix3& Matrix3() noexcept;
        constexpr const JFMatrix3& Matrix3() const noexcept;

    public:
        JFMatrix3 matrix3;
    };
}

#include "JFLinearTransform3.inl"