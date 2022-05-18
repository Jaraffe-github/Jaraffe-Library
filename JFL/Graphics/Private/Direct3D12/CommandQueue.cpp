//
//  File: CommandQueue.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "CommandQueue.h"
#include "SwapChain.h"

using namespace JFL;

CommandQueue::CommandQueue(GraphicsDevice* device, ID3D12CommandQueue* queue)
	: queue(queue)
	, device(device)
{
}

JFObject<JFSwapChain> CommandQueue::CreateSwapChain(const JFWindow* window)
{
	return new SwapChain(device, this, window);
}
