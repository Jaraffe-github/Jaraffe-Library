//
//  File: JFFile.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"
#include "String/JFString.h"

namespace JFL
{
	class JFL_API JFFile final : public JFRefCounter
	{
	public:
		enum class OpenMode
		{
			Existing = 0,	// error if it doesn't exist.
			Truncate,		// opening the file truncates the file if it exists, create if it doesn't exist.
			Append,			// each write operation appends to the file, create if it doesn't exist.
		};
		enum class AccessMode
		{
			ReadOnly = 0,	// ignore commands about write. (ignore open mode with truncate or append)
			WriteOnly,		// ignore commands about open.
			ReadWrite,
		};
		enum class SeekOrigin
		{
			Start,			// Indicates that the offset should be set to the specified value.
			End,			// Indicates that the offset should be set to the size of the file plus the specified number of bytes.
			Current,		// Indicates that the offset should be set to the specified number of bytes after the current location.
		};

		~JFFile();

		static JFObject<JFFile> Open(const JFStringW& path, AccessMode accessMode, OpenMode openMode, bool binary);
		static JFObject<JFFile> OpenText(const JFStringW& path, AccessMode accessMode, OpenMode openMode);
		static JFObject<JFFile> OpenBinary(const JFStringW& path, AccessMode accessMode, OpenMode openMode);
		static bool Delete(const JFStringW& path);
		static bool IsExist(const JFStringW& path);

		size_t Read(void* buffer, size_t byteToRead) const;
		size_t Write(const void* buffer, size_t byteToWrite);

		size_t Seek(size_t offset, SeekOrigin seekOrigin = SeekOrigin::Start);

		size_t CurrentPosition() const;
		size_t TotalLength() const;
		size_t RemainLength() const;

		const JFStringW& FileName() const;
		const JFStringW& Extension() const;
		const JFStringW& RelativePath() const;
		const JFStringW& AbsolutePath() const;

	private:
		JFFile();
		JFFile(const JFFile&) = delete;
		JFFile& operator = (const JFFile&) = delete;

		void* impl;
		size_t fileSize;
		JFStringW fileName;
		JFStringW extension;
		JFStringW relativePath;
		JFStringW absolutePath;
	};
}
