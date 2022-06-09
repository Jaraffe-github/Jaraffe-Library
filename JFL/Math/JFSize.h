//
//  File: JFSize.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFSize final
    {
    public:
        constexpr JFSize();
        constexpr JFSize(float width, float height);

        constexpr JFSize operator+(const JFSize& s) const noexcept;
        constexpr JFSize operator-(const JFSize& s) const noexcept;
        constexpr JFSize operator*(float f) const noexcept;
        constexpr JFSize operator/(float f) const noexcept;

        constexpr JFSize& operator+=(const JFSize& s) noexcept;
        constexpr JFSize& operator-=(const JFSize& s) noexcept;
        constexpr JFSize& operator*=(float f) const noexcept;
        constexpr JFSize& operator/=(float f) const noexcept;

        float width;
        float height;
    };

    constexpr JFSize::JFSize()
        : width(0.f), height(0.f)
    {}
    constexpr JFSize::JFSize(float width, float height)
        : width(width), height(height)
    {}
    constexpr JFSize JFSize::operator+(const JFSize& s) const noexcept
    {
        return { width + s.width, height + s.height };
    }
    constexpr JFSize JFSize::operator-(const JFSize& s) const noexcept
    {
        return { width - s.width, height - s.height };
    }
    constexpr JFSize JFSize::operator*(float f) const noexcept
    {
        return { width * f, height * f };
    }
    constexpr JFSize JFSize::operator/(float f) const noexcept
    {
        return { width / f, height / f };
    }

    constexpr JFSize& JFSize::operator+=(const JFSize& s) noexcept
    {
        width += s.width;
        height += s.height;
    }
    constexpr JFSize& JFSize::operator-=(const JFSize& s) noexcept
    {
        width -= s.width;
        height -= s.height;
    }
    constexpr JFSize& JFSize::operator*=(float f) const noexcept
    {
        width -= f;
        height -= f;
    }
    constexpr JFSize& JFSize::operator/=(float f) const noexcept
    {
        width /= f;
        height /= f;
    }
}
