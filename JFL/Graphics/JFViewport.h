//
//  File: JFViewport.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Math/JFMath.h"

namespace JFL
{
    class JFViewport final
    {
    public:
        constexpr JFViewport();
        constexpr JFViewport(JFPoint origin, JFSize size, float nearDepth, float farDepth);
        constexpr JFViewport(float x, float y, float width, float height, float nearDepth, float farDepth);

        union
        {
            struct
            {
                JFPoint origin;
                JFSize size;
                float nearDepth;
                float farDepth;
            };
            struct
            {
                float x, y;
                float width, height;
            };
        };
    };

    constexpr JFViewport::JFViewport()
        : origin(), size(), nearDepth(0.f), farDepth(0.f)
    {}
    constexpr JFViewport::JFViewport(JFPoint origin, JFSize size, float nearDepth, float farDepth)
        : origin(origin), size(size), nearDepth(nearDepth), farDepth(farDepth)
    {}
    constexpr JFViewport::JFViewport(float x, float y, float width, float height, float nearDepth, float farDepth)
        : origin(x, y), size(width, height), nearDepth(nearDepth), farDepth(farDepth)
    {}
}