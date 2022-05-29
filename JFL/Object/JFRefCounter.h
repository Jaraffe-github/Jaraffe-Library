//
//  File: JFRefCounter.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFRefCounter
	{
	public: 
		JFRefCounter();
		virtual ~JFRefCounter() noexcept;

		uint32_t AddRef();
		uint32_t Release();
		uint32_t RefCount() const;

	private:
		struct JFL_API std::atomic<unsigned int> refCount;
	}; 
}