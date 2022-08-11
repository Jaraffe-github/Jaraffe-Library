//
//  File: JFQuaternion.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFVector3;
    class JFQuaternion final
    {
    public:
        constexpr JFQuaternion() noexcept;
        explicit JFQuaternion(float pitch, float yaw, float roll) noexcept;
        explicit JFQuaternion(const JFVector3& axis, float angle) noexcept;
        explicit constexpr JFQuaternion(float x, float y, float z, float w) noexcept;
        ~JFQuaternion() noexcept = default;

        static constexpr float Dot(const JFQuaternion& q1, const JFQuaternion& q2);
        static constexpr JFQuaternion Slerp(const JFQuaternion& q1, const JFQuaternion& q2, float t);

        constexpr JFQuaternion operator+(const JFQuaternion& q) const noexcept;
        constexpr JFQuaternion operator*(const JFQuaternion& q) const noexcept;

        constexpr JFQuaternion& operator+=(const JFQuaternion& q) noexcept;
        constexpr JFQuaternion& operator*=(const JFQuaternion& q) noexcept;

        constexpr JFVector3 Euler() const;

        inline float Length() const noexcept;
        constexpr float LengthSq() const noexcept;
        constexpr JFQuaternion& Inverse() noexcept;
        constexpr JFQuaternion& Normalize() noexcept;

        constexpr bool IsUnitQuaternion(float tolerance = 1.0e-6f) const noexcept;

        static const JFQuaternion identity;

        float x, y, z, w;
    };
}

#include "JFQuaternion.inl"
