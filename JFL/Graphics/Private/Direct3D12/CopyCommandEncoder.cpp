//
//  File: CopyCommandEncoder.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CopyCommandEncoder.h"
#include "Texture.h"
#include "GPUBuffer.h"

using namespace JFL;
using namespace JFL::Private::Direct3D12;

CopyCommandEncoder::CopyCommandEncoder(CommandBuffer* commandBuffer, ID3D12GraphicsCommandList* commandList)
	: commandBuffer(commandBuffer)
	, commandList(commandList)
{
}

void CopyCommandEncoder::CopyBufferToBuffer(JFGPUBuffer* src, size_t srcOffset, JFGPUBuffer* dest, size_t destOffset, size_t copySize)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    GPUBuffer* destBuffer = dynamic_cast<GPUBuffer*>(dest);
    JFASSERT_DEBUG(srcBuffer);
    JFASSERT_DEBUG(destBuffer);

    ID3D12Resource* srcRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* destRawBuffer = destBuffer->Buffer();
    JFASSERT_DEBUG(srcRawBuffer);
    JFASSERT_DEBUG(destRawBuffer);

    TransitionBufferState(destRawBuffer, destBuffer->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->CopyBufferRegion(destRawBuffer, destOffset, srcRawBuffer, srcOffset, copySize);
    TransitionBufferState(destRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, destBuffer->InitialState());
}

void CopyCommandEncoder::CopyBufferToTexture(JFGPUBuffer* src, size_t srcOffset, JFTexture* dest, TextureArea destArea)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    Texture* destTexture = dynamic_cast<Texture*>(dest);
    JFASSERT_DEBUG(srcBuffer);
    JFASSERT_DEBUG(destTexture);

    ID3D12Resource* gpuRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* textureRawBuffer = destTexture->Resource();
    JFASSERT_DEBUG(gpuRawBuffer);
    JFASSERT_DEBUG(textureRawBuffer);

    TransitionBufferState(textureRawBuffer, destTexture->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);

    // It for interpreting buffer as a texture.
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT bufferFootprint;
    D3D12_RESOURCE_DESC textureDesc = textureRawBuffer->GetDesc();
    bufferFootprint.Offset = 0;
    bufferFootprint.Footprint.Format = textureDesc.Format;
    bufferFootprint.Footprint.Width = destArea.width;
    bufferFootprint.Footprint.Height = destArea.height;
    bufferFootprint.Footprint.Depth = textureDesc.DepthOrArraySize;
    bufferFootprint.Footprint.RowPitch = AlignTextureRowPitch(destArea.width * PixelFormatSize(destTexture->Format()));

    // like texture. (ref footprint)
    D3D12_BOX bufferBounds;
    bufferBounds.top = 0;
    bufferBounds.bottom = destArea.height;
    bufferBounds.left = static_cast<UINT>(srcOffset);
    bufferBounds.right = destArea.width;
    bufferBounds.front = 0;
    bufferBounds.back = 1;

    CD3DX12_TEXTURE_COPY_LOCATION destCopyLocation(textureRawBuffer, 0);
    CD3DX12_TEXTURE_COPY_LOCATION srcCopyLocation(gpuRawBuffer, bufferFootprint);
    commandList->CopyTextureRegion(&destCopyLocation, destArea.x, destArea.y, 0, &srcCopyLocation, &bufferBounds);

    TransitionBufferState(textureRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, destTexture->InitialState());
}

void CopyCommandEncoder::CopyTextureToBuffer(JFTexture* src, TextureArea srcArea, JFGPUBuffer* dest, size_t destOffset)
{
    Texture* srcTexture = dynamic_cast<Texture*>(src);
    GPUBuffer* destBuffer = dynamic_cast<GPUBuffer*>(dest);
    JFASSERT_DEBUG(srcTexture);
    JFASSERT_DEBUG(destBuffer);

    ID3D12Resource* gpuRawBuffer = destBuffer->Buffer();
    ID3D12Resource* textureRawBuffer = srcTexture->Resource();
    JFASSERT_DEBUG(gpuRawBuffer);
    JFASSERT_DEBUG(textureRawBuffer);

    TransitionBufferState(textureRawBuffer, srcTexture->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);

    // It for interpreting buffer as a texture.
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT bufferFootprint;
    D3D12_RESOURCE_DESC textureDesc = textureRawBuffer->GetDesc();
    bufferFootprint.Offset = 0;
    bufferFootprint.Footprint.Format = textureDesc.Format;
    bufferFootprint.Footprint.Width = srcArea.width;
    bufferFootprint.Footprint.Height = srcArea.height;
    bufferFootprint.Footprint.Depth = textureDesc.DepthOrArraySize;
    bufferFootprint.Footprint.RowPitch = AlignTextureRowPitch(srcArea.width * PixelFormatSize(srcTexture->Format()));

    D3D12_BOX textureBounds;
    textureBounds.top = srcArea.y;
    textureBounds.bottom = srcArea.height;
    textureBounds.left = srcArea.x;
    textureBounds.right = srcArea.width;
    textureBounds.front = 0;
    textureBounds.back = 1;

    CD3DX12_TEXTURE_COPY_LOCATION destCopyLocation(gpuRawBuffer, bufferFootprint);
    CD3DX12_TEXTURE_COPY_LOCATION srcCopyLocation(textureRawBuffer, 0);
    commandList->CopyTextureRegion(&destCopyLocation, static_cast<UINT>(destOffset), 0, 0, &srcCopyLocation, &textureBounds);

    TransitionBufferState(textureRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, srcTexture->InitialState());
}

void CopyCommandEncoder::EndEncoding()
{
    commandList->Close();
    commandBuffer->AddEncodedCommandList(commandList.Get());
    commandList = nullptr;
}

void CopyCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
    if (before != after)
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
        commandList->ResourceBarrier(1, &barrier);
    }
}
