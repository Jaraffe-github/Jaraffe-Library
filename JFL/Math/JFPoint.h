//
//  File: JFPoint.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFPoint final
    {
    public:
        constexpr JFPoint();
        constexpr JFPoint(float x, float y);

        constexpr JFPoint operator+(const JFPoint& p) const noexcept;
        constexpr JFPoint operator-(const JFPoint& p) const noexcept;

        constexpr JFPoint& operator+=(const JFPoint& p) noexcept;
        constexpr JFPoint& operator-=(const JFPoint& p) noexcept;

        float x;
        float y;
    };

    constexpr JFPoint::JFPoint()
        : x(0.f), y(0.f)
    {}
    constexpr JFPoint::JFPoint(float x, float y)
        : x(x), y(y)
    {}
    constexpr JFPoint JFPoint::operator+(const JFPoint& p) const noexcept
    {
        return { x + p.x, y + p.y };
    }
    constexpr JFPoint JFPoint::operator-(const JFPoint& p) const noexcept
    {
        return { x - p.x, y - p.y };
    }
    constexpr JFPoint& JFPoint::operator+=(const JFPoint& p) noexcept
    {
        x += p.x;
        y += p.y;
    }
    constexpr JFPoint& JFPoint::operator-=(const JFPoint& p) noexcept
    {
        x -= p.x;
        y -= p.y;
    }
}