//
//  File: WindowContext.h
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include "JFInclude.h"
#include "../../JFWindowContextInterface.h"
#include <UIKit/UIKit.h>

namespace JFL
{
    class WindowContext : public JFWindowContextInterface
    {
    public:
        WindowContext();
        ~WindowContext() = default;

        void Create() override;
        void Destory() override;

        void Show() override;
        void Hide() override;

        void* PlatformHandle() const override;
        
    private:
        UIWindow* window;
        UIView* view;
    };
}

#endif
#endif
