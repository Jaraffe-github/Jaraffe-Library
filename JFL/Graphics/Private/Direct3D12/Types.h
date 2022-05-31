//
//  File: Types.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFPixelFormat.h"
#include "d3d12_headers.h"

namespace JFL
{
    inline DXGI_FORMAT PixelFormat(JFPixelFormat format)
    {
        switch (format)
        {
        case JFPixelFormat::RGBA8Unorm:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case JFPixelFormat::RGBA8Snorm:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case JFPixelFormat::RGBA8Uint:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case JFPixelFormat::RGBA8Sint:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case JFPixelFormat::Depth24UnormStencil8:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    inline JFPixelFormat PixelFormat(DXGI_FORMAT format)
    {
        switch (format)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return JFPixelFormat::RGBA8Unorm;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return JFPixelFormat::RGBA8Snorm;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return JFPixelFormat::RGBA8Uint;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return JFPixelFormat::RGBA8Sint;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return JFPixelFormat::Depth24UnormStencil8;
        }
        return JFPixelFormat::Invalid;
    }
}
