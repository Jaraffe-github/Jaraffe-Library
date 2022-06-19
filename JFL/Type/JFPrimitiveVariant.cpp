//
//  File: JFPrimitiveVariant.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFPrimitiveVariant.h"

using namespace JFL;

JFPrimitiveVariant::JFPrimitiveVariant()
    : activeType(Type::None)
    , block{ 0 }
{
}

JFPrimitiveVariant::JFPrimitiveVariant(const bool v) noexcept
    : activeType(Type::Boolean)
    , block{ 0 }
{
    new (block) bool(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const int32_t v) noexcept
    : activeType(Type::Int32)
    , block{ 0 }
{
    new (block) int32_t(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const int64_t v) noexcept
    : activeType(Type::Int64)
    , block{ 0 }
{
    new (block) int64_t(v);
}


JFPrimitiveVariant::JFPrimitiveVariant(const uint32_t v) noexcept
    : activeType(Type::UInt32)
    , block{ 0 }
{
    new (block) uint32_t(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const uint64_t v) noexcept
    : activeType(Type::UInt64)
    , block{ 0 }
{
    new (block) uint64_t(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const long v) noexcept
    : activeType(Type::Long)
    , block{ 0 }
{
    new (block) long(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const unsigned long v) noexcept
    : activeType(Type::ULong)
    , block{ 0 }
{
    new (block) unsigned long(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const float v) noexcept
    : activeType(Type::Float)
    , block{ 0 }
{
    new (block) float(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const double v) noexcept
    : activeType(Type::Double)
    , block{ 0 }
{
    new (block) double(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const long double v) noexcept
    : activeType(Type::Double)
    , block{ 0 }
{
    new (block) double(v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const char* v) noexcept
    : activeType(Type::Char)
    , block{ 0 }
{
    new (block) const char* (v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const wchar_t* v) noexcept
    : activeType(Type::WChar)
    , block{ 0 }
{
    new (block) const wchar_t* (v);
}

JFPrimitiveVariant::JFPrimitiveVariant(const void* v) noexcept
    : JFPrimitiveVariant((uintptr_t)v)
{
}

bool JFPrimitiveVariant::Boolean()
{
    JFASSERT_DEBUG(activeType == Type::Boolean);
    return reinterpret_cast<bool*>(block)[0];
}

int32_t JFPrimitiveVariant::Int32()
{
    JFASSERT_DEBUG(activeType == Type::Int32);
    return reinterpret_cast<int32_t*>(block)[0];
}

int64_t JFPrimitiveVariant::Int64()
{
    JFASSERT_DEBUG(activeType == Type::Int64);
    return reinterpret_cast<int64_t*>(block)[0];
}

uint32_t JFPrimitiveVariant::UInt32()
{
    JFASSERT_DEBUG(activeType == Type::UInt32);
    return reinterpret_cast<uint32_t*>(block)[0];
}

uint64_t JFPrimitiveVariant::UInt64()
{
    JFASSERT_DEBUG(activeType == Type::UInt64);
    return reinterpret_cast<uint64_t*>(block)[0];
}

long JFPrimitiveVariant::Long()
{
    JFASSERT_DEBUG(activeType == Type::Long);
    return reinterpret_cast<long*>(block)[0];
}

unsigned long JFPrimitiveVariant::ULong()
{
    JFASSERT_DEBUG(activeType == Type::ULong);
    return reinterpret_cast<unsigned long*>(block)[0];
}

float JFPrimitiveVariant::Float()
{
    JFASSERT_DEBUG(activeType == Type::Float);
    return reinterpret_cast<float*>(block)[0];
}

double JFPrimitiveVariant::Double()
{
    JFASSERT_DEBUG(activeType == Type::Double);
    return reinterpret_cast<double*>(block)[0];
}

const char* JFPrimitiveVariant::Char()
{
    JFASSERT_DEBUG(activeType == Type::Char);
    return reinterpret_cast<const char**>(block)[0];
}

const wchar_t* JFPrimitiveVariant::WChar()
{
    JFASSERT_DEBUG(activeType == Type::WChar);
    return reinterpret_cast<const wchar_t**>(block)[0];
}
