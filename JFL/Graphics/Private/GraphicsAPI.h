//
//  File: GraphicsAPI.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../JFGraphicsDevice.h"
#include "Log/JFLog.h"

namespace JFL::Private
{
#if defined(_WIN32)
	namespace Direct3D12
	{
		JFGraphicsDevice* CreateGraphicsDevice();
	}
#endif

	namespace Vulkan
	{
		JFGraphicsDevice* CreateGraphicsDevice();
	}

	namespace Metal
	{

	}

	JFGraphicsDevice* CreateGraphicsDevice(JFGraphicsType type)
	{
		switch (type)
		{
#if defined(_WIN32)
		case JFGraphicsType::Direct3D12:
			return Direct3D12::CreateGraphicsDevice();
#endif
		case JFGraphicsType::Vulkan:
			return Vulkan::CreateGraphicsDevice();
		}
		JFLogError(L"not supported graphics type [{}].", static_cast<int>(type));
		return nullptr;
	}
}
