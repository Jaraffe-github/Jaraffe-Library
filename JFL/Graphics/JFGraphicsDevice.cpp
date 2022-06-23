//
//  File: JFGraphicsDevice.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "JFGraphicsDevice.h"
#include "Private/GraphicsAPI.h"
#include "FileSystem/JFFileSystem.h"

using namespace JFL;

JFGraphicsDevice* JFGraphicsDevice::CreateGraphicsDevice(JFGraphicsType type)
{
    return JFL::Private::CreateGraphicsDevice(type);
}

JFObject<JFShader> JFGraphicsDevice::CreateShader(const JFStringW& path, const JFStringA& entry, JFShader::StageType stage)
{
	if (JFObject<JFFile> file = JFFile::OpenBinary(path, JFFile::AccessMode::ReadOnly, JFFile::OpenMode::Existing))
	{
		size_t fileLength = file->TotalLength();

		JFArray<uint8_t> code(fileLength);
		file->Read(code.Data(), fileLength);
		return CreateShader(code, entry, stage);
	}
	return nullptr;
}
