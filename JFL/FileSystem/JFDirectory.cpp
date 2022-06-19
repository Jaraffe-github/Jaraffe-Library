//
//  File: JFDirectory.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFDirectory.h"
#include <filesystem>

using namespace JFL;

JFObject<JFDirectory> JFDirectory::Open(const JFStringW& path)
{
	if (IsExist(path))
	{
		if (JFDirectory* directory = new JFDirectory())
		{
			std::filesystem::path p(path.Data());
			directory->directoryName = p.filename().c_str();
			directory->relativePath = p.relative_path().c_str();
			directory->absolutePath = std::filesystem::canonical(p).c_str();
			directory->Reload();
			return directory;
		}
	}
	return nullptr;
}

bool JFDirectory::Create(const JFStringW& path, bool recursive)
{
	std::filesystem::path p(path.Data());
	if (recursive)
		return std::filesystem::create_directories(p);
	else 
		return std::filesystem::create_directory(p);
}

bool JFDirectory::Delete(const JFStringW& path, bool emptied)
{
	if (IsExist(path))
	{
		std::filesystem::path p(path.Data());
		if (emptied)
			return std::filesystem::remove(p);
		else
			return std::filesystem::remove_all(p);
	}
	return false;
}

bool JFDirectory::IsExist(const JFStringW& path)
{
	std::filesystem::path p(path.Data());
	return std::filesystem::exists(p) && std::filesystem::is_directory(p);
}

JFObject<JFFile> JFDirectory::OpenFile(const JFStringW& fileName, JFFile::AccessMode accessMode, JFFile::OpenMode openMode, bool binary)
{
	return JFFile::Open(JFStringFormat::Format(L"{}/{}", absolutePath, fileName), 
						accessMode, openMode, binary);
}

JFObject<JFFile> JFDirectory::OpenFile(size_t index, JFFile::AccessMode accessMode, JFFile::OpenMode openMode, bool binary)
{
	return JFFile::Open(JFStringFormat::Format(L"{}/{}", absolutePath, FileNameAtIndex(index)),
						accessMode, openMode, binary);
}

JFObject<JFDirectory> JFDirectory::OpenSubdirectory(const JFStringW& directoryName)
{
	return JFDirectory::Open(JFStringFormat::Format(L"{}/{}", absolutePath, directoryName));
}

JFObject<JFDirectory> JFDirectory::OpenSubdirectory(size_t index)
{
	return JFDirectory::Open(JFStringFormat::Format(L"{}/{}", absolutePath, SubdirectoryNameAtIndex(index)));
}

size_t JFDirectory::NumberOfFiles() const
{
	return files.Count();
}

size_t JFDirectory::NumberOfSubdirectories() const
{
	return subdirectories.Count();
}

const JFStringW& JFDirectory::FileNameAtIndex(size_t index) const
{
	JFASSERT_DEBUG(files.Count() > index);
	return files[index];
}

const JFStringW& JFDirectory::SubdirectoryNameAtIndex(size_t index) const
{
	JFASSERT_DEBUG(subdirectories.Count() > index);
	return subdirectories[index];
}

const JFStringW& JFDirectory::DirectoryName() const
{
	return directoryName;
}

const JFStringW& JFDirectory::AbsolutePath() const
{
	return absolutePath;
}

const JFStringW& JFDirectory::RelativePath() const
{
	return relativePath;
}

void JFDirectory::Reload()
{
	std::filesystem::path p(absolutePath.Data());
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		if (entry.is_regular_file())
			files.Add(entry.path().filename().c_str());
		else
			subdirectories.Add(entry.path().filename().c_str());
	}
}
