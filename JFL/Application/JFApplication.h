//
//  File: JFApplication.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFApplicationContextInterface.h"

namespace JFL
{
	class JFL_API JFApplication
	{
	public:
		JFApplication();
		virtual ~JFApplication();

		int Run();

	protected:
		virtual void OnInitialize() = 0;
		virtual void OnTerminate() = 0;

	private:
		JFApplicationContextInterface* context;
	};
}
