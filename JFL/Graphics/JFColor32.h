//
//  File: JFColor32.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
    class JFColor32 final
    {      
    public:
        constexpr JFColor32();
        constexpr explicit JFColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
        constexpr explicit JFColor32(uint32_t value);

        constexpr bool operator != (const JFColor32& c) const;
        constexpr bool operator == (const JFColor32& c) const;

        constexpr JFColor32 operator + (const JFColor32& c) const;
        constexpr JFColor32 operator - (const JFColor32& c) const;

        constexpr JFColor32& operator += (const JFColor32& c);
        constexpr JFColor32& operator -= (const JFColor32& c);

        union
        {
            struct
            {
                uint8_t r, g, b, a;
            };
            uint32_t value;
        };
    };

    constexpr JFColor32::JFColor32()
        : r(0), g(0), b(0), a(255)
    {}
    constexpr JFColor32::JFColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r), g(g), b(b), a(a)
    {}
    constexpr JFColor32::JFColor32(uint32_t value)
        : value(value)
    {}

    constexpr bool JFColor32::operator==(const JFColor32& c) const
    {
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }
    constexpr bool JFColor32::operator!=(const JFColor32& c) const
    {
        return r != c.r || g != c.g || b != c.b || a != c.a;
    }

    constexpr JFColor32 JFColor32::operator+(const JFColor32& c) const
    {
        return JFColor32(
            static_cast<uint8_t>(JFNumeric::Clamp(r + c.r, 0, 255)),
            static_cast<uint8_t>(JFNumeric::Clamp(g + c.g, 0, 255)),
            static_cast<uint8_t>(JFNumeric::Clamp(b + c.b, 0, 255)),
            static_cast<uint8_t>(JFNumeric::Clamp(a + c.a, 0, 255)));
    }
    constexpr JFColor32 JFColor32::operator-(const JFColor32& c) const
    {
        return JFColor32(
             static_cast<uint8_t>(JFNumeric::Clamp(r - c.r, 0, 255)),
             static_cast<uint8_t>(JFNumeric::Clamp(g - c.g, 0, 255)),
             static_cast<uint8_t>(JFNumeric::Clamp(b - c.b, 0, 255)),
             static_cast<uint8_t>(JFNumeric::Clamp(a - c.a, 0, 255)));
    }

    constexpr JFColor32& JFColor32::operator+=(const JFColor32& c)
    {
        r = static_cast<uint8_t>(JFNumeric::Clamp(r + c.r, 0, 255));
        g = static_cast<uint8_t>(JFNumeric::Clamp(g + c.g, 0, 255));
        b = static_cast<uint8_t>(JFNumeric::Clamp(b + c.b, 0, 255));
        a = static_cast<uint8_t>(JFNumeric::Clamp(a + c.a, 0, 255));
        return *this;
    }
    constexpr JFColor32& JFColor32::operator-=(const JFColor32& c)
    {
        r = static_cast<uint8_t>(JFNumeric::Clamp(r - c.r, 0, 255));
        g = static_cast<uint8_t>(JFNumeric::Clamp(g - c.g, 0, 255));
        b = static_cast<uint8_t>(JFNumeric::Clamp(b - c.b, 0, 255));
        a = static_cast<uint8_t>(JFNumeric::Clamp(a - c.a, 0, 255));
        return *this;
    }
}
