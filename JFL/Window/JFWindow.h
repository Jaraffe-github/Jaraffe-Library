//
//  File: JFWindow.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFWindowContextInterface.h"

namespace JFL
{
	class JFL_API JFWindow final
	{
	public:
		JFWindow();
		~JFWindow();

		void Create();
		void Destory();

		void Show();
		void Hide();

		void* PlatformHandle() const;

	private:
		JFWindowContextInterface* context;
	};
}
