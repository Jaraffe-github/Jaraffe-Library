//
//  File: JFApplicationContextInterface.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

namespace JFL
{
	class JFL_API JFApplicationContextInterface
	{
	public:
		JFApplicationContextInterface() = default;
		virtual ~JFApplicationContextInterface() = default;

		virtual int MessageLoop() = 0;
	};
}
