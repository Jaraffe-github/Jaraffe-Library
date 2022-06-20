//
//  File: JFShader.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "String/JFString.h"
#include "Container/JFArray.h"

namespace JFL
{
    class JFL_API JFShader : public JFRefCounter
    {
    public:
        enum class StageType
        {
            Vertex,
            Fragment,
        };

        JFShader() = default;
        virtual ~JFShader() = default;
    };
}
