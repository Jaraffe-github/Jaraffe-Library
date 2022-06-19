//
//  File: JFStringFormat.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "JFString.h"
#include "JFStringW.h"
#include "Type/JFType.h"
#include <vector>

namespace JFL
{
	class JFL_API JFStringFormat
	{
	public:
		template<class... Args> static JFStringA Format(const char* format, Args&&... args)
		{
			return JFStringFormat::FormatArray(format, std::vector<JFPrimitiveVariant>{JFPrimitiveVariant(std::forward<Args>(args))...});
		}
		template<class... Args> static JFStringW Format(const wchar_t* format, Args&&... args)
		{
			return JFStringFormat::FormatArray(format, std::vector<JFPrimitiveVariant>{JFPrimitiveVariant(std::forward<Args>(args))...});
		}
		
	private:
		static JFStringA FormatArray(const char* format, const std::vector<JFPrimitiveVariant>& arguments);
		static JFStringW FormatArray(const wchar_t* format, const std::vector<JFPrimitiveVariant>& arguments);
	};
}
