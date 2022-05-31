//
//  File: JFPixelFormat.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "Log/JFLog.h"

namespace JFL
{
    // TODO: you can add and delete it if necessary while using it
    // ref: https://developer.apple.com/documentation/metal/mtlpixelformat
    enum class JFPixelFormat
    {
        Invalid,

        // RGBA 8
        RGBA8Unorm,
        RGBA8Snorm,
        RGBA8Uint,
        RGBA8Sint,

        // Depth Stencil
        Depth24UnormStencil8,
    };

    inline uint32_t PixelFormatSize(JFPixelFormat format)
    {
        switch (format)
        {
        case JFPixelFormat::RGBA8Unorm:
        case JFPixelFormat::RGBA8Snorm:
        case JFPixelFormat::RGBA8Uint:
        case JFPixelFormat::RGBA8Sint:
        case JFPixelFormat::Depth24UnormStencil8:
            return 4;

        default:
            JFLogError("Not supported pixel format: {}", static_cast<uint32_t>(format));
        }
        return 0;
    }
}
