//
//  File: JFGModel.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFL.h"
#include "JFGInclude.h"

namespace JFG
{
    struct JFGVertex
    {
        JFVector3 pos;
        JFVector3 normal;
        JFLinearColor color;
        // JFVector2 texcoord;
    };

    struct JFGMesh
    {
        JFArray<JFGVertex> vertices;
        JFObject<JFGPUBuffer> vertexBuffer;
    };

    struct JFGMaterial
    {
        JFLinearColor diffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
        JFVector3 fresnelR0 = { 0.01f, 0.01f, 0.01f };
        float roughness = 0.25f;
        JFMatrix4 matTransform = {};
    };

    struct JFGModel
    {
        JFMatrix4 world;
        JFMatrix4 texTransform;

        JFArray<JFGMesh> meshes;
        JFGMaterial material;
    };
}
