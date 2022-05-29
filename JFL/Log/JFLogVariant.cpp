//
//  File: JFLogVariant.cpp
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFLogVariant.h"

using namespace JFL;

JFLogVariant::JFLogVariant()
    : activeType(Type::None)
    , block{ 0 }
{
}

JFLogVariant::JFLogVariant(const bool v) noexcept
    : activeType(Type::Boolean)
    , block{ 0 }
{
    new (block) bool(v);
}

JFLogVariant::JFLogVariant(const int32_t v) noexcept
    : activeType(Type::Int32)
    , block{ 0 }
{
    new (block) int32_t(v);
}

JFLogVariant::JFLogVariant(const int64_t v) noexcept
    : activeType(Type::Int64)
    , block{ 0 }
{
    new (block) int64_t(v);
}


JFLogVariant::JFLogVariant(const uint32_t v) noexcept
    : activeType(Type::UInt32)
    , block{ 0 }
{
    new (block) uint32_t(v);
}

JFLogVariant::JFLogVariant(const uint64_t v) noexcept
    : activeType(Type::UInt64)
    , block{ 0 }
{
    new (block) uint64_t(v);
}

JFLogVariant::JFLogVariant(const long v) noexcept
    : activeType(Type::Long)
    , block{ 0 }
{
    new (block) long(v);
}

JFLogVariant::JFLogVariant(const unsigned long v) noexcept
    : activeType(Type::ULong)
    , block{ 0 }
{
    new (block) unsigned long(v);
}

JFLogVariant::JFLogVariant(const float v) noexcept
    : activeType(Type::Float)
    , block{ 0 }
{
    new (block) float(v);
}

JFLogVariant::JFLogVariant(const double v) noexcept
    : activeType(Type::Double)
    , block{ 0 }
{
    new (block) double(v);
}

JFLogVariant::JFLogVariant(const long double v) noexcept
    : activeType(Type::Double)
    , block{ 0 }
{
    new (block) double(v);
}

JFLogVariant::JFLogVariant(const char* v) noexcept
    : activeType(Type::Char)
    , block{ 0 }
{
    new (block) const char* (v);
}

JFLogVariant::JFLogVariant(const wchar_t* v) noexcept
    : activeType(Type::WChar)
    , block{ 0 }
{
    new (block) const wchar_t* (v);
}

JFLogVariant::JFLogVariant(const void* v) noexcept
    : JFLogVariant((uintptr_t)v)
{
}

bool JFLogVariant::Boolean()
{
    JFASSERT_DEBUG(activeType == Type::Boolean);
    return reinterpret_cast<bool*>(block)[0];
}

int32_t JFLogVariant::Int32()
{
    JFASSERT_DEBUG(activeType == Type::Int32);
    return reinterpret_cast<int32_t*>(block)[0];
}

int64_t JFLogVariant::Int64()
{
    JFASSERT_DEBUG(activeType == Type::Int64);
    return reinterpret_cast<int64_t*>(block)[0];
}

uint32_t JFLogVariant::UInt32()
{
    JFASSERT_DEBUG(activeType == Type::UInt32);
    return reinterpret_cast<uint32_t*>(block)[0];
}

uint64_t JFLogVariant::UInt64()
{
    JFASSERT_DEBUG(activeType == Type::UInt64);
    return reinterpret_cast<uint64_t*>(block)[0];
}

long JFLogVariant::Long()
{
    JFASSERT_DEBUG(activeType == Type::Long);
    return reinterpret_cast<long*>(block)[0];
}

unsigned long JFLogVariant::ULong()
{
    JFASSERT_DEBUG(activeType == Type::ULong);
    return reinterpret_cast<unsigned long*>(block)[0];
}

float JFLogVariant::Float()
{
    JFASSERT_DEBUG(activeType == Type::Float);
    return reinterpret_cast<float*>(block)[0];
}

double JFLogVariant::Double()
{
    JFASSERT_DEBUG(activeType == Type::Double);
    return reinterpret_cast<double*>(block)[0];
}

const char* JFLogVariant::Char()
{
    JFASSERT_DEBUG(activeType == Type::Char);
    return reinterpret_cast<const char**>(block)[0];
}

const wchar_t* JFLogVariant::WChar()
{
    JFASSERT_DEBUG(activeType == Type::WChar);
    return reinterpret_cast<const wchar_t**>(block)[0];
}
