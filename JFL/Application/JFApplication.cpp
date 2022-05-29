//
//  File: JFApplication.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFApplication.h"
#include "Private/ApplicationPlatform.h"

using namespace JFL;

JFApplication::JFApplication()
	: context(nullptr)
{
	context = CreateApplicationContext();
	JFASSERT_DEBUG(context);
}

JFApplication::~JFApplication()
{
	JFASSERT_DEBUG(context);
	delete context;
	context = nullptr;
}

int JFApplication::Run()
{
	OnInitialize();

	JFASSERT_DEBUG(context);
	int exitCode = context->MessageLoop();

	OnTerminate();
	return exitCode;
}
