//
//  File: WindowContext.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "../../JFWindow.h"
#include "JFInclude.h"
#include <UIKit/UIKit.h>

namespace JFL::Private::CocoaTouch
{
    class Window : public JFWindow
    {
    public:
        Window();
        ~Window() = default;

        void Create(const JFWindowDescriptor& descriptor) override;
        void Destory() override;

        void Show() override;
        void Hide() override;
        
        JFStringW Title() const override;
        void SetTitle(const JFStringW& title) override;
        
        float DpiScale() const override { return 1.0f; }

        void* PlatformHandle() const override;
        
    private:
        UIWindow* window;
        UIView* view;
    };
}
