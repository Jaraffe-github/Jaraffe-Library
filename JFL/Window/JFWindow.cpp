//
//  File: JFWindow.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFWindow.h"
#include "Private/WindowPlatform.h"

using namespace JFL;

JFWindow::JFWindow()
	: context(nullptr)
{
	context = CreateWindowContext();
	JFASSERT_DEBUG(context);
}

JFWindow::~JFWindow()
{
	JFASSERT_DEBUG(context);
	delete context;
	context = nullptr;
}

void JFWindow::Create()
{
	JFASSERT_DEBUG(context);
	context->Create();
}

void JFWindow::Destory()
{
	JFASSERT_DEBUG(context);
	context->Destory();
}

void JFWindow::Show()
{
	JFASSERT_DEBUG(context);
	context->Show();
}

void JFWindow::Hide()
{
	JFASSERT_DEBUG(context);
	context->Hide();
}

void* JFWindow::PlatformHandle() const
{
	JFASSERT_DEBUG(context);
	return context->PlatformHandle();
}
