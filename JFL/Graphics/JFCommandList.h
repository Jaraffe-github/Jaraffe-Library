//
//  File: JFCommandList.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Object/JFObject.h"

namespace JFL
{
	class JFL_API JFCommandList : public JFRefCounter
	{
	public:
		JFCommandList() = default;
		virtual ~JFCommandList() noexcept = default;
	};
}
