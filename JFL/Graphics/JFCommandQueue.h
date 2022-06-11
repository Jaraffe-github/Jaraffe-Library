//
//  File: JFCommandQueue.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "JFSwapChain.h"
#include "JFCommandBuffer.h"

namespace JFL
{
	class JFWindow;

	class JFL_API JFCommandQueue : public JFRefCounter
	{
	public:
		JFCommandQueue() = default;
		virtual ~JFCommandQueue() noexcept = default;

		virtual JFObject<JFSwapChain> CreateSwapChain(const JFWindow*) = 0;
		virtual JFObject<JFCommandBuffer> CreateCommandBuffer() = 0;

		virtual void WaitComplete() = 0;
	};
}
