//
//  File: JFGraphicsDevice.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFGraphicsDevice.h"
#include "Private/GraphicsAPI.h"

#include "Private/Direct3D12/GraphicsDevice.h"

using namespace JFL;

JFGraphicsDevice* JFGraphicsDevice::CreateGraphicsDevice()
{
    return JFL::Private::CreateGraphicsDevice();
}
