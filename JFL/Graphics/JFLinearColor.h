//
//  File: JFLinearColor.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFColor32.h"
#include "Math/JFMath.h"

namespace JFL
{
    class JFL_API JFLinearColor final
    {
    public:
        constexpr JFLinearColor();
        constexpr JFLinearColor(float r, float g, float b, float a = 1.f);
        constexpr JFLinearColor(uint16_t r, uint16_t g, uint16_t b, uint16_t a = 255, uint16_t colorDepth = 8);
        constexpr explicit JFLinearColor(JFColor32 color32);
        constexpr explicit JFLinearColor(const JFVector3& v);
        constexpr explicit JFLinearColor(const JFVector4& v);

        constexpr bool operator != (const JFLinearColor& c) const;
        constexpr bool operator == (const JFLinearColor& c) const;

        constexpr JFLinearColor operator + (const JFLinearColor& c) const;
        constexpr JFLinearColor operator - (const JFLinearColor& c) const;
        constexpr JFLinearColor operator * (const JFLinearColor& c) const;
        constexpr JFLinearColor operator * (float f) const;

        constexpr JFLinearColor& operator += (const JFLinearColor& c);
        constexpr JFLinearColor& operator -= (const JFLinearColor& c);
        constexpr JFLinearColor& operator *= (const JFLinearColor& c);
        constexpr JFLinearColor& operator *= (float f);

        constexpr JFVector3 Vector3() const { return { r, g, b }; }
        constexpr JFVector4 Vector4() const { return { r, g, b, a }; }

        static const JFLinearColor white;
        static const JFLinearColor black;
        static const JFLinearColor red;
        static const JFLinearColor green;
        static const JFLinearColor blue;

        union
        {
            struct
            {
                float r, g, b, a;
            };
            float value[4];
        };
    };

    constexpr JFLinearColor::JFLinearColor()
        : r(0.f), g(0.f), b(0.f), a(1.f)
    {}
    constexpr JFLinearColor::JFLinearColor(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a)
    {}
    constexpr JFLinearColor::JFLinearColor(uint16_t r, uint16_t g, uint16_t b, uint16_t a, uint16_t colorDepth)
        : JFLinearColor()
    {
        JFASSERT_DEBUG(colorDepth > 0);

        // https://www.notion.so/Color-Depth-bits-per-pixel-752c120da81c4d0aa954626fa723daf3
        float factor = 1.f / ((1 << colorDepth) - 1);
        this->r = r * factor;
        this->g = g * factor;
        this->b = b * factor;
        this->a = a * factor;
    }
    constexpr JFLinearColor::JFLinearColor(JFColor32 color32)
    {
        constexpr float factor = { 1.f / 255.f };
        r = static_cast<float>(color32.r) * factor;
        g = static_cast<float>(color32.g) * factor;
        b = static_cast<float>(color32.b) * factor;
        a = static_cast<float>(color32.a) * factor;

    }
    constexpr JFLinearColor::JFLinearColor(const JFVector3& v)
        : r(v.x), g(v.y), b(v.z), a(1.f)
    {}
    constexpr JFLinearColor::JFLinearColor(const JFVector4& v)
        : r(v.x), g(v.y), b(v.z), a(v.w)
    {}

    constexpr bool JFLinearColor::operator==(const JFLinearColor& c) const
    {
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }
    constexpr bool JFLinearColor::operator!=(const JFLinearColor& c) const
    {
        return r != c.r || g != c.g || b != c.b || a != c.a;
    }

    constexpr JFLinearColor JFLinearColor::operator+(const JFLinearColor& c) const
    {
        return { r + c.r, g + c.g, b + c.b, a + c.a };
    }
    constexpr JFLinearColor JFLinearColor::operator-(const JFLinearColor& c) const
    {
        return { r - c.r, g - c.g, b - c.b, a - c.a };
    }
    constexpr JFLinearColor JFLinearColor::operator*(const JFLinearColor& c) const
    {
        return { r * c.r, g * c.g, b * c.b, a * c.a };
    }
    constexpr JFLinearColor JFLinearColor::operator*(float f) const
    {
        return { r * f, g * f, b * f, a * f };
    }

    constexpr JFLinearColor& JFLinearColor::operator+=(const JFLinearColor& c)
    {
        r = r + c.r;
        g = g + c.g;
        b = b + c.b;
        a = a + c.a;
        return *this;
    }
    constexpr JFLinearColor& JFLinearColor::operator-=(const JFLinearColor& c)
    {
        r = r - c.r;
        g = g - c.g;
        b = b - c.b;
        a = a - c.a;
        return *this;
    }
    constexpr JFLinearColor& JFLinearColor::operator*=(const JFLinearColor& c)
    {
        r = r * c.r;
        g = g * c.g;
        b = b * c.b;
        a = a * c.a;
        return *this;
    }
    constexpr JFLinearColor& JFLinearColor::operator*=(float f)
    {
        r = r * f;
        g = g * f;
        b = b * f;
        a = a * f;
        return *this;
    }
}
