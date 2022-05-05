//
//  File: JFAffineTransform3.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFMatrix3.h"
#include "JFVector3.h"

namespace JFL
{
    class JFMatrix4;
    class JFLinearTransform3;
    class JFAffineTransform3 final
    {
    public:
        constexpr JFAffineTransform3() noexcept;
        constexpr JFAffineTransform3(const JFMatrix4& m) noexcept;

        constexpr bool operator == (const JFAffineTransform3& at) const noexcept;
        constexpr bool operator != (const JFAffineTransform3& at) const noexcept;

        constexpr JFAffineTransform3& Translate(float x, float y, float z) noexcept;
        constexpr JFAffineTransform3& Translate(const JFVector3& v) noexcept;
        constexpr JFAffineTransform3& Multiply(const JFLinearTransform3& lt) noexcept;
        constexpr JFAffineTransform3& Multiply(const JFAffineTransform3& at) noexcept;

        constexpr JFMatrix4 Matrix4() const noexcept;
        constexpr const JFMatrix3& Matrix3() const noexcept;

    public:
        JFMatrix3 matrix3;
        JFVector3 translation;
    };
}

#include "JFAffineTransform3.inl"