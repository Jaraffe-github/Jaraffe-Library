//
//  File: JFTexture.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "Container/JFContainer.h"

namespace JFL
{
    enum class JFVertexFormat
    {
        Invalid = 0,

        Float,
        Float2,
        Float3,
        Float4,
    };

    struct JFVertexAttributeDescriptor
    {
        JFVertexFormat format;
        const char* semanticName;
        uint32_t semanticIndex;
        uint32_t offset;
    };

    struct JFVertexDescriptor
    {
        JFArray<JFVertexAttributeDescriptor> attributes;
    };
}
