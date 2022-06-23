//
//  File: RenderPipeline.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFRenderPipeline.h"
#include "d3d12_headers.h"

namespace JFL::Private::Direct3D12
{
    class RenderPipeline final : public JFRenderPipeline
    {
    public:
        RenderPipeline(ID3D12PipelineState*, ID3D12RootSignature*);
        ~RenderPipeline() noexcept = default;

        ID3D12PipelineState* PipelineState() const { return pipelineState.Get(); }
        ID3D12RootSignature* RootSignature() const { return rootSignature.Get(); }

    private:
        ComPtr<ID3D12PipelineState> pipelineState;
        ComPtr<ID3D12RootSignature> rootSignature;
    };
}
