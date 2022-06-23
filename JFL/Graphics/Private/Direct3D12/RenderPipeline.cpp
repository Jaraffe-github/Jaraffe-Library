//
//  File: RenderPipeline.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "RenderPipeline.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

RenderPipeline::RenderPipeline(ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature)
    : pipelineState(pipelineState)
    , rootSignature(rootSignature)
{
}
