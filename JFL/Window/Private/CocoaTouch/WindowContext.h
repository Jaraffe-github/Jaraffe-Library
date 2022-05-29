//
//  File: WindowContext.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
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
