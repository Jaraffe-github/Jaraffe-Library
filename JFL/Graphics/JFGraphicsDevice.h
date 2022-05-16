//
//  File: JFGraphicsDevice.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFGraphicsDevice
	{
	public:
		virtual ~JFGraphicsDevice() noexcept = default;

		static JFGraphicsDevice* CreateGraphicsDevice();

	protected:
		JFGraphicsDevice() = default;
	};
}
