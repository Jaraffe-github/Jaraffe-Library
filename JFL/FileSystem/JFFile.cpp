//
//  File: JFFile.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFFile.h"
#include <fstream>
#include <filesystem>

using namespace JFL;

namespace Private
{
	struct FileHandle
	{
		FileHandle(std::fstream& _stream)
		{
			_stream.swap(stream);
		}
		std::fstream stream;
	};
}

JFFile::JFFile()
	: impl(nullptr)
	, fileSize(0)
{
}

JFFile::~JFFile()
{
	if (impl)
	{
		auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
		handle->stream.close();

		delete impl;
		impl = nullptr;
	}
}

JFObject<JFFile> JFFile::Open(const JFStringW& path, AccessMode accessMode, OpenMode openMode, bool binary)
{
	std::ios_base::openmode mode = std::ios_base::in;
	switch (accessMode)
	{
	case JFFile::AccessMode::WriteOnly:
		mode = std::ios_base::out;
		break;
	case JFFile::AccessMode::ReadWrite:
		mode = std::ios_base::in | std::ios_base::out;
		break;
	}
	if (accessMode != AccessMode::ReadOnly)
	{
		switch (openMode)
		{
		case JFFile::OpenMode::Truncate:
			mode |= std::ios_base::trunc;
			break;
		case JFFile::OpenMode::Append:
			mode |= std::ios_base::app;
			break;
		}
	}
	if (binary)
		mode |= std::ios_base::binary;

	std::fstream stream(path, mode);
	if (stream.is_open())
	{
		if (JFFile* file = new JFFile)
		{
			file->impl = new Private::FileHandle(stream);
			Private::FileHandle* fileHandle = reinterpret_cast<Private::FileHandle*>(file->impl);

			std::filesystem::path p(path.Data());
			{
				file->fileName = p.filename().c_str();
				file->extension = p.extension().c_str();
				file->absolutePath = std::filesystem::canonical(p).c_str();
				file->relativePath = p.relative_path().c_str();
				file->fileSize = std::filesystem::file_size(p);
			}
			return file;
		}
	}
	return nullptr;
}

JFObject<JFFile> JFFile::OpenText(const JFStringW& path, AccessMode accessMode, OpenMode openMode)
{
	return JFFile::Open(path, accessMode, openMode, false);
}

JFObject<JFFile> JFFile::OpenBinary(const JFStringW& path, AccessMode accessMode, OpenMode openMode)
{
	return JFFile::Open(path, accessMode, openMode, true);
}

bool JFFile::Delete(const JFStringW& path)
{
	if (IsExist(path))
		return std::filesystem::remove(std::filesystem::path(path.Data()));
	return false;
}

bool JFFile::IsExist(const JFStringW& path)
{
	auto p = std::filesystem::path(path.Data());
	return std::filesystem::exists(p) && 
		// https://www.tecmint.com/explanation-of-everything-is-a-file-and-types-of-files-in-linux/
		std::filesystem::is_regular_file(p); // for linux.
}

size_t JFFile::Read(void* buffer, size_t byteToRead) const
{
	JFASSERT_DEBUG(buffer);

	auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
	size_t readableSize = Min(byteToRead, RemainLength());
	if (readableSize > 0)
		handle->stream.read((char*)buffer, readableSize);
	return readableSize;
}

size_t JFFile::Write(const void* buffer, size_t byteToWrite)
{
	JFASSERT_DEBUG(buffer);

	auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
	handle->stream.write((const char*)buffer, byteToWrite);
	handle->stream.flush();
	size_t currentPosition = CurrentPosition();
	if (currentPosition > fileSize)
		fileSize = currentPosition;
	return byteToWrite;
}

size_t JFFile::TotalLength() const
{
	return fileSize;
}

size_t JFFile::RemainLength() const
{
	auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
	size_t currentPosition = handle->stream.tellg();
	if (currentPosition > fileSize)
		return 0;
	return fileSize - currentPosition;
}

const JFStringW& JFFile::FileName() const
{
	return fileName;
}

const JFStringW& JFFile::Extension() const
{
	return extension;
}

const JFStringW& JFFile::RelativePath() const
{
	return relativePath;
}

const JFStringW& JFFile::AbsolutePath() const
{
	return absolutePath;
}

size_t JFFile::CurrentPosition() const
{
	auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
	return handle->stream.tellg();
}

size_t JFFile::Seek(size_t offset, SeekOrigin seekOrigin)
{
	std::ios_base::seekdir dir = std::ios_base::beg;
	switch (seekOrigin)
	{
	case SeekOrigin::Current:
		dir = std::ios_base::cur;
		break;
	case SeekOrigin::End:
		dir = std::ios_base::end;
		break;
	}

	auto handle = reinterpret_cast<::Private::FileHandle*>(impl);
	handle->stream.seekg(offset, dir);
	return handle->stream.tellg();
}
