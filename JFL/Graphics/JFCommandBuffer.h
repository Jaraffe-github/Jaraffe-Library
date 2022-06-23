//
//  File: JFCommandBuffer.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFRenderCommandEncoder.h"
#include "JFCopyCommandEncoder.h"
#include "Object/JFObject.h"

namespace JFL
{
	class JFL_API JFCommandBuffer : public JFRefCounter
	{
	public:
		JFCommandBuffer() = default;
		virtual ~JFCommandBuffer() noexcept = default;

		virtual JFObject<JFRenderCommandEncoder> CreateRenderCommandEncoder() = 0;
		virtual JFObject<JFCopyCommandEncoder> CreateCopyCommandEncoder() = 0;

		virtual void Commit() = 0;
	};
}
