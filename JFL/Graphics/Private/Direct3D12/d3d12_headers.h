//
//  File: d3d12_headers.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <wrl.h>
#include <system_error>
#include <D3Dcompiler.h>
#include <dxgidebug.h>

using namespace Microsoft::WRL;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        auto msg = std::system_category().message(hr);
        throw std::exception(msg.c_str());
    }
}

constexpr inline uint32_t AlignGPUBufferSize(size_t size)
{
    constexpr uint32_t alignmentSize = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT - 1;
    return (size + alignmentSize) & ~(alignmentSize);
}

constexpr inline uint32_t AlignTextureRowPitch(size_t size)
{
#if (defined(XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
    constexpr uint32_t alignmentSize = D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT - 1;
#else
    constexpr uint32_t alignmentSize = D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1;
#endif
    return (size + alignmentSize) & ~(alignmentSize);
}
