//
//  File: Types.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFPixelFormat.h"
#include "../../JFVertexDescriptor.h"
#include "../../JFRenderPipeline.h"
#include "../../JFBlendState.h"
#include "d3d12_headers.h"

namespace JFL::Private::Direct3D12
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

    inline DXGI_FORMAT VertexFormat(JFVertexFormat format)
    {
        switch (format)
        {
        case JFVertexFormat::Float:
            return DXGI_FORMAT_D32_FLOAT;
        case JFVertexFormat::Float2:
            return DXGI_FORMAT_R32G32_FLOAT;
        case JFVertexFormat::Float3:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case JFVertexFormat::Float4:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    inline D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveType(JFPrimitiveTopologyType type)
    {
        switch (type)
        {
        case JFPrimitiveTopologyType::Point:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
        case JFPrimitiveTopologyType::Line:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
        case JFPrimitiveTopologyType::Triangle:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        }
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
    }

    inline D3D12_BLEND_OP BlendOperation(JFBlendOperation type)
    {
        switch (type)
        {
        case JFBlendOperation::Add:
            return D3D12_BLEND_OP_ADD;
        case JFBlendOperation::Subtract:
            return D3D12_BLEND_OP_SUBTRACT;
        case JFBlendOperation::ReverseSubtract:
            return D3D12_BLEND_OP_REV_SUBTRACT;
        case JFBlendOperation::Min:
            return D3D12_BLEND_OP_MIN;
        case JFBlendOperation::Max:
            return D3D12_BLEND_OP_MAX;
        default:
            JFASSERT_DEBUG(false);
        }
        return D3D12_BLEND_OP_ADD;
    }

    inline D3D12_BLEND BlendFactor(JFBlendFactor type)
    {
        switch (type)
        {
        case JFBlendFactor::Zero:
            return D3D12_BLEND_ZERO;
        case JFBlendFactor::One:
            return D3D12_BLEND_ONE;
        case JFBlendFactor::SourceColor:
            return D3D12_BLEND_SRC_COLOR;
        case JFBlendFactor::OneMinusSourceColor:
            return D3D12_BLEND_INV_SRC_COLOR;
        case JFBlendFactor::SourceAlpha:
            return D3D12_BLEND_SRC_ALPHA;
        case JFBlendFactor::OneMinusSourceAlpha:
            return D3D12_BLEND_INV_SRC_ALPHA;
        case JFBlendFactor::DestinationColor:
            return D3D12_BLEND_DEST_COLOR;
        case JFBlendFactor::OneMinusDestinationColor:
            return D3D12_BLEND_INV_DEST_COLOR;
        case JFBlendFactor::DestinationAlpha:
            return D3D12_BLEND_DEST_ALPHA;
        case JFBlendFactor::OneMinusDestinationAlpha:
            return D3D12_BLEND_INV_DEST_ALPHA;
        case JFBlendFactor::SourceAlphaSaturated:
            return D3D12_BLEND_SRC_ALPHA_SAT;
        case JFBlendFactor::BlendFactor:
            return D3D12_BLEND_BLEND_FACTOR;
        case JFBlendFactor::OneMinusBlendFactor:
            return D3D12_BLEND_INV_BLEND_FACTOR;
        default:
            JFASSERT_DEBUG(false);
        }
        return D3D12_BLEND_ONE;
    }
}
