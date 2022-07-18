//
//  File: JFGLight.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFL.h"
#include "JFGInclude.h"

namespace JFG
{
    struct JFGLight
    {
        JFVector3 strength = { 0.5f, 0.5f, 0.5f };
        float falloffStart = 1.0f;                          // point/spot light only
        JFVector3 direction = { 0.0f, -1.0f, 0.0f };        // directional/spot light only
        float falloffEnd = 10.0f;                           // point/spot light only
        JFVector3 position = { 0.0f, 0.0f, 0.0f };          // point/spot light only
        float spotPower = 64.0f;                            // spot light only
    };
}
