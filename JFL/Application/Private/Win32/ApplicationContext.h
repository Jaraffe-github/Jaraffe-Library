//
//  File: ApplicationContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#if defined(_WIN32)
#include "JFInclude.h"
#include "../../JFApplicationContextInterface.h"

namespace JFL
{
	class ApplicationContext : public JFApplicationContextInterface
	{
	public:
		ApplicationContext() = default;
		~ApplicationContext() = default;

		int MessageLoop() override;
	};
}

#endif
