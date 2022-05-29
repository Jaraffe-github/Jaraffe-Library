//
//  File: JFGraphicsDevice.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "JFCommandQueue.h"
#include "JFCommandList.h"

namespace JFL
{
	class JFL_API JFGraphicsDevice : public JFRefCounter
	{
	public:
		virtual ~JFGraphicsDevice() noexcept = default;

		virtual JFObject<JFCommandQueue> CreateCommandQueue() = 0;
		virtual JFObject<JFCommandList> CreateCommandList() = 0;

		static JFGraphicsDevice* CreateGraphicsDevice();

	protected:
		JFGraphicsDevice() = default;
	};
}
