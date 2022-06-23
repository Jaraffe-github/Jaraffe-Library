//
//  File: SwapChain.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "Shader.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

Shader::Shader(ID3DBlob* byteCode, JFShader::StageType stage, const JFStringA& entry)
	: stage(stage)
	, entry(entry)
	, byteCode(byteCode)
{

}

D3D12_SHADER_BYTECODE Shader::ByteCode() const
{
	return { reinterpret_cast<BYTE*>(byteCode->GetBufferPointer()), byteCode->GetBufferSize() };
}
