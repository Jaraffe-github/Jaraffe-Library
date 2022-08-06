//
//  File: JFCoordinateConverter.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFVector2.h"

namespace JFL
{
    namespace JFCoordinateConverter
    {
        // Cartesian coordinate -> Polar coordinate
        static constexpr JFVector2 ConvertToPolarCoordFromCartesianCoord(const JFVector2& cartesianCoord);

        // Polar coordinate -> Cartesian coordinate
        static constexpr JFVector2 ConvertToCartesianCoordFromPolarCoord(const JFVector2& polarCoord);
    };
}

//=============================================================================
// Implementation)
//=============================================================================
namespace JFL
{
    namespace JFCoordinateConverter
    {
        constexpr JFVector2 ConvertToPolarCoordFromCartesianCoord(const JFVector2& cartesianCoord)
        {
            return { cartesianCoord.Length(), cartesianCoord.Angle() };
        }

        constexpr JFVector2 ConvertToCartesianCoordFromPolarCoord(const JFVector2& polarCoord)
        {
            return { polarCoord.x * std::cos(polarCoord.y), polarCoord.x * std::sin(polarCoord.y) };
        }
    }
}
