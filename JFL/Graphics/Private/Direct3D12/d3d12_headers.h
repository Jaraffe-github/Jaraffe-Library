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

#if defined(DEBUG) || defined(_DEBUG)
#include <dxgidebug.h>
#endif

using namespace Microsoft::WRL;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        auto msg = std::system_category().message(hr);
        throw std::exception(msg.c_str());
    }
}

namespace GraphicsOption
{
    constexpr bool ENABLE_DEBUG_LAYER = 1;
    constexpr bool ENABLE_GPU_VALIDATION = 1;
    constexpr D3D_FEATURE_LEVEL MIN_FEATURE = D3D_FEATURE_LEVEL_11_0;
}
