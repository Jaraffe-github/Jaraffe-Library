//
//  File: VulkanUtils.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFPixelFormat.h"
#include "../../JFGPUBuffer.h"
#include "../../JFVertexDescriptor.h"
#include "VulkanHeaders.h"

namespace JFL::Private::Vulkan
{
    namespace Tool
    {
        static JFStringA ErrorString(VkResult errorCode)
        {
            switch (errorCode)
            {
#define STR(r) case VK_ ##r: return #r
                STR(NOT_READY);
                STR(TIMEOUT);
                STR(EVENT_SET);
                STR(EVENT_RESET);
                STR(INCOMPLETE);
                STR(ERROR_OUT_OF_HOST_MEMORY);
                STR(ERROR_OUT_OF_DEVICE_MEMORY);
                STR(ERROR_INITIALIZATION_FAILED);
                STR(ERROR_DEVICE_LOST);
                STR(ERROR_MEMORY_MAP_FAILED);
                STR(ERROR_LAYER_NOT_PRESENT);
                STR(ERROR_EXTENSION_NOT_PRESENT);
                STR(ERROR_FEATURE_NOT_PRESENT);
                STR(ERROR_INCOMPATIBLE_DRIVER);
                STR(ERROR_TOO_MANY_OBJECTS);
                STR(ERROR_FORMAT_NOT_SUPPORTED);
                STR(ERROR_SURFACE_LOST_KHR);
                STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
                STR(SUBOPTIMAL_KHR);
                STR(ERROR_OUT_OF_DATE_KHR);
                STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
                STR(ERROR_VALIDATION_FAILED_EXT);
                STR(ERROR_INVALID_SHADER_NV);
#undef STR
            default:
                return "UNKNOWN_ERROR";
            }
        }
    }

    namespace Converter
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

        inline VkFormat VertexFormat(JFVertexFormat format)
        {
            switch (format)
            {
            case JFVertexFormat::Float:
                return VkFormat::VK_FORMAT_R32_SFLOAT;
            case JFVertexFormat::Float2:
                return VkFormat::VK_FORMAT_R32G32_SFLOAT;
            case JFVertexFormat::Float3:
                return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
            case JFVertexFormat::Float4:
                return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
            }
            return VK_FORMAT_UNDEFINED;
        }

        inline VkBufferUsageFlagBits BufferUsage(JFGPUBuffer::Usage usage)
        {
            int flags = 0;

            if (static_cast<uint8_t>(usage) & static_cast<uint8_t>(JFGPUBuffer::UsageIndexBuffer))
                flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

            if (static_cast<uint8_t>(usage) & static_cast<uint8_t>(JFGPUBuffer::UsageVertexBuffer))
                flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

            return static_cast<VkBufferUsageFlagBits>(flags);
        }

        inline VkSharingMode BufferSharingMode(JFGPUBuffer::SharingMode mode)
        {
            switch (mode)
            {
            case JFGPUBuffer::SharingMode::Exclusive:
                return VK_SHARING_MODE_EXCLUSIVE;
            case JFGPUBuffer::SharingMode::Concurrent:
                return VK_SHARING_MODE_CONCURRENT;
            }
            return VK_SHARING_MODE_EXCLUSIVE;
        }

        inline VkMemoryPropertyFlags MemoryPropertyFlags(JFGPUBuffer::MemoryLocation memoryLocation, JFGPUBuffer::CPUCacheMode cacheMode)
        {
            VkMemoryPropertyFlags memoryPropertyFlags = 0;

            switch (memoryLocation)
            {
            case JFGPUBuffer::MemoryLocation::GPUOnly:
                memoryPropertyFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
                break;

            case JFGPUBuffer::MemoryLocation::CPUAndGPU:
                memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
                break;
            }

            switch (cacheMode)
            {
            case JFGPUBuffer::CPUCacheMode::ReadCombined:
                memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
                break;
            case JFGPUBuffer::CPUCacheMode::Synchronized:
                memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
                break;
            }

            return memoryPropertyFlags;
        }
    }

    inline void ThrowIfFailed(VkResult result)
    {
        if (result != VK_SUCCESS)
        {
            auto msg = Tool::ErrorString(result);
            throw std::runtime_error(msg.Data());
        }
    }
}
