//
//  File: Types.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFPixelFormat.h"
#include "vulkan_headers.h"

namespace JFL::Private::Vulkan
{
    inline VkFormat PixelFormat(JFPixelFormat format)
    {
        switch (format)
        {
        case JFPixelFormat::RGBA8Unorm:
            return VK_FORMAT_R8G8B8A8_UNORM;
        case JFPixelFormat::RGBA8Snorm:
            return VK_FORMAT_R8G8B8A8_SNORM;
        case JFPixelFormat::RGBA8Uint:
            return VK_FORMAT_R8G8B8A8_UINT;
        case JFPixelFormat::RGBA8Sint:
            return VK_FORMAT_R8G8B8A8_SINT;
        case JFPixelFormat::Depth24UnormStencil8:
            return VK_FORMAT_D24_UNORM_S8_UINT;
        }
        return VK_FORMAT_UNDEFINED;
    }

    inline JFPixelFormat PixelFormat(VkFormat format)
    {
        switch (format)
        {
        case VK_FORMAT_R8G8B8A8_UNORM:
            return JFPixelFormat::RGBA8Unorm;
        case VK_FORMAT_R8G8B8A8_SNORM:
            return JFPixelFormat::RGBA8Snorm;
        case VK_FORMAT_R8G8B8A8_UINT:
            return JFPixelFormat::RGBA8Uint;
        case VK_FORMAT_R8G8B8A8_SINT:
            return JFPixelFormat::RGBA8Sint;
        case VK_FORMAT_D24_UNORM_S8_UINT:
            return JFPixelFormat::Depth24UnormStencil8;
        }
        return JFPixelFormat::Invalid;
    }
}
