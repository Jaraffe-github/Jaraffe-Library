//
//  File: shader.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFShader.h"
#include "d3d12_headers.h"

namespace JFL::Private::Direct3D12
{
    class Shader final : public JFShader
    {
    public:
        Shader(ID3DBlob* byteCode, JFShader::StageType stage, const JFStringA& entry);
        ~Shader() noexcept = default;

        D3D12_SHADER_BYTECODE ByteCode() const;

    private:
        JFShader::StageType stage;
        JFStringA entry;
        ComPtr<ID3DBlob> byteCode;
    };
}
