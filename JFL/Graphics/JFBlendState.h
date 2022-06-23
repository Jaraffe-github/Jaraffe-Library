//
//  File: JFBlendState.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once

namespace JFL
{
    enum JFColorWriteMask
    {
        ColorWriteMaskNone = 0x0,
        ColorWriteMaskRed = 0x1,
        ColorWriteMaskGreen = 0x2,
        ColorWriteMaskBlue = 0x4,
        ColorWriteMaskAlpha = 0x8,
        ColorWriteMaskAll = 0xf,
    };

    enum class JFBlendOperation
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max
    };

    enum class JFBlendFactor
    {
        Zero,
        One,
        SourceColor,
        OneMinusSourceColor,
        SourceAlpha,
        OneMinusSourceAlpha,
        DestinationColor,
        OneMinusDestinationColor,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        SourceAlphaSaturated,
        BlendFactor,
        OneMinusBlendFactor,
    };
}