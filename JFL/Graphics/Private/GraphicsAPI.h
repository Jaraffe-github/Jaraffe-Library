//
//  File: GraphicsAPI.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFGraphicsDevice.h"

namespace JFL::Private
{
#if defined(_WIN32)
	namespace Direct3D
	{
		JFGraphicsDevice* CreateGraphicsDevice();
	}
#endif

	namespace Vulkan
	{

	}

	namespace Metal
	{

	}

	JFGraphicsDevice* CreateGraphicsDevice()
	{
		return Direct3D::CreateGraphicsDevice();
	}
}
