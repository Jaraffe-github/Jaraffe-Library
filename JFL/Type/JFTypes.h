//
//  File: JFTypes.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once

namespace JFL
{
    //=============================================================================
    // Template Basic Type)
    //=============================================================================
	template<bool B>
	struct JFBool
	{
		enum { Value = B };
	};
	using JFTrue = JFBool<true>;
	using JFFalse = JFBool<false>;

    template<int Num>
    struct JFNumber
    {
        enum { Value = Num };
    };

    //=============================================================================
    // Conditional)
    //=============================================================================
    template<bool B, class T, class F>
    struct JFConditional;

	template<class T, class F>
    struct JFConditional<1, T, F>
    {
		using Type = T;
    };
    template<class T, class F>
    struct JFConditional<0, T, F>
    {
		using Type = F;
    };
}
