//
//  File: JFRect.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFPoint.h"
#include "JFSize.h"

namespace JFL
{
    class JFRect final
    {
    public:
        constexpr JFRect();
        constexpr JFRect(JFPoint origin, JFSize size);
        constexpr JFRect(float x, float y, float width, float height);

        constexpr bool Intersect(const JFRect& rect) const;
        constexpr bool IsInside(const JFRect& rect) const;
        constexpr bool IsInside(const JFPoint& point) const;

        constexpr JFPoint LeftTop() const;
        constexpr JFPoint RightTop() const;
        constexpr JFPoint LeftBottom() const;
        constexpr JFPoint RightBottom() const;

        union
        {
            struct
            {
                JFPoint origin;
                JFSize size;
            };
            struct
            {
                float x, y;
                float width, height;
            };
        };
    };

    constexpr JFRect::JFRect()
        : x(0.f), y(0.f), width(0.f), height(0.f)
    {}
    constexpr JFRect::JFRect(JFPoint origin, JFSize size)
        : x(origin.x), y(origin.y), width(size.width), height(size.height)
    {}
    constexpr JFRect::JFRect(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height)
    {}

    constexpr bool JFRect::Intersect(const JFRect& r) const
    {
        JFPoint rb = RightBottom();
        JFPoint rb2 = r.RightBottom();
		return x <= rb2.x && r.x <= rb.x && y <= rb2.y && r.y <= rb.y;
	}
	constexpr bool JFRect::IsInside(const JFRect& r) const
    {
        return x <= r.x && y <= r.y && width >= r.width && height >= r.height;
    }
    constexpr bool JFRect::IsInside(const JFPoint& p) const
    {
        JFPoint rb = RightBottom();
        return x <= p.x && y <= p.y && rb.x >= p.x && rb.y >= p.y;
    }

	constexpr JFPoint JFRect::LeftTop() const
	{
		return { x, y };
	}
	constexpr JFPoint JFRect::RightTop() const
	{
		return { x + width, y };
	}
	constexpr JFPoint JFRect::LeftBottom() const
	{
		return { x, y + height };
	}
	constexpr JFPoint JFRect::RightBottom() const
	{
		return { x + width, y + height };
	}
}