//
//  File: JFRenderCommandEncoder.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFViewport.h"
#include "JFLinearColor.h"
#include "Math/JFMath.h"
#include "Object/JFObject.h"
#include <vector>

namespace JFL
{
    class JFTexture;
    class JFGPUBuffer;

    class JFL_API JFRenderCommandEncoder : public JFRefCounter
    {
    public:
        enum class DepthStencilClearFlag
        {
            Depth,
            Stencil,
            All,
        };

        JFRenderCommandEncoder() = default;
        virtual ~JFRenderCommandEncoder() noexcept = default;

        virtual void SetViewport(const JFViewport& viewport) = 0;
        virtual void SetViewports(const JFViewport* viewports, uint32_t count) = 0;
        virtual void SetScissorRect(const JFRect& rect) = 0;
        virtual void SetScissorRects(const JFRect* rects, uint32_t count) = 0;

        virtual void SetRenderTargets(std::vector<const JFTexture*> renderTargets, const JFTexture* depthStencil) = 0;
        virtual void ClearRenderTargetView(const JFTexture* renderTarget, const JFLinearColor& clearColor) = 0;
        virtual void ClearDepthStencilView(const JFTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;

        virtual void EndEncoding() = 0;
    };
}
