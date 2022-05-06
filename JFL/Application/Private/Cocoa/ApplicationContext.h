//
//  File: ApplicationContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_OSX
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
#endif
