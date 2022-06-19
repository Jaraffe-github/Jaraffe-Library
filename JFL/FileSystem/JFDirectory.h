//
//  File: JFDirectory.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFFile.h"
#include "Object/JFObject.h"
#include "String/JFString.h"
#include "Container/JFContainer.h"

namespace JFL
{
	class JFL_API JFDirectory final : public JFRefCounter
	{
	public:
		~JFDirectory() = default;

		static JFObject<JFDirectory> Open(const JFStringW& path);
		static bool Create(const JFStringW& path, bool recursive=false);
		static bool Delete(const JFStringW& path, bool emptied=true);
		static bool IsExist(const JFStringW& path);

		JFObject<JFFile> OpenFile(const JFStringW& fileName, JFFile::AccessMode accessMode, JFFile::OpenMode openMode, bool binary);
		JFObject<JFFile> OpenFile(size_t index, JFFile::AccessMode accessMode, JFFile::OpenMode openMode, bool binary);
		JFObject<JFDirectory> OpenSubdirectory(const JFStringW& directoryName);
		JFObject<JFDirectory> OpenSubdirectory(size_t index);

		size_t NumberOfFiles() const;
		size_t NumberOfSubdirectories() const;
		const JFStringW& FileNameAtIndex(size_t index) const;
		const JFStringW& SubdirectoryNameAtIndex(size_t index) const;

		const JFStringW& DirectoryName() const;
		const JFStringW& AbsolutePath() const;
		const JFStringW& RelativePath() const;

		void Reload();

	private:
		JFDirectory() = default;
		JFDirectory(const JFDirectory&) = delete;
		JFDirectory& operator = (const JFDirectory&) = delete;

		JFStringW directoryName;
		JFStringW relativePath;
		JFStringW absolutePath;
		class JFL_API JFArray<JFStringW> files;
		class JFL_API JFArray<JFStringW> subdirectories;
	};
}
