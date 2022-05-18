//
//  File: JFCommandQueue.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "JFSwapChain.h"

namespace JFL
{
	class JFWindow;

	class JFL_API JFCommandQueue : public JFRefCounter
	{
	public:
		JFCommandQueue() = default;
		virtual ~JFCommandQueue() noexcept = default;

		virtual JFObject<JFSwapChain> CreateSwapChain(const JFWindow*) = 0;
	};
}
