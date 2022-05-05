//
//  File: JFVector4.inl
//  Author: Seungmin Choi (ccm1333@naver.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFMatrix4.h"

namespace JFL
{
	constexpr JFVector4::JFVector4() noexcept
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	constexpr JFVector4::JFVector4(float x, float y, float z, float w) noexcept
		: x(x), y(y), z(z), w(w)
	{
	}

	constexpr float JFVector4::Dot(const JFVector4& v1, const JFVector4& v2) noexcept
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
	}

	constexpr bool JFVector4::operator==(const JFVector4& v) const noexcept
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	constexpr bool JFVector4::operator!=(const JFVector4& v) const noexcept
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	constexpr JFVector4 JFVector4::operator+(const JFVector4& v) const noexcept
	{
		return { x + v.x, y + v.y, z + v.z, w + v.w };
	}

	constexpr JFVector4 JFVector4::operator-() const noexcept
	{
		return { -x, -y, -z, -w };
	}

	constexpr JFVector4 JFVector4::operator-(const JFVector4& v) const noexcept
	{
		return { x - v.x, y - v.y, z - v.z, w - v.w };
	}

	constexpr JFVector4 JFVector4::operator*(const JFMatrix4& m) const noexcept
	{
		return { x * m._11 + y * m._21 + z * m._31 + w * m._41
			   , x * m._12 + y * m._22 + z * m._32 + w * m._42
			   , x * m._13 + y * m._23 + z * m._33 + w * m._43
			   , x * m._14 + y * m._24 + z * m._34 + w * m._44 };
	}

	constexpr JFVector4 JFVector4::operator*(float f) const noexcept
	{
		return { x * f, y * f, z * f, w * f };
	}

	constexpr JFVector4 JFVector4::operator/(const JFVector4& v) const noexcept
	{
		return { x / v.x, y / v.y, z / v.z, w / v.w };
	}

	constexpr static JFVector4 operator*(float f, const JFVector4& v) noexcept
	{
		return { v.x * f, v.y * f, v.z * f, v.w * f };
	}

	constexpr JFVector4& JFVector4::operator+=(const JFVector4& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	constexpr JFVector4& JFVector4::operator-=(const JFVector4& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	constexpr JFVector4& JFVector4::operator*=(const JFMatrix4& m) noexcept
	{
		JFVector4 v{ *this };
		x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
		y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
		z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
		w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;
		return *this;
	}

	constexpr JFVector4& JFVector4::operator*=(float f) noexcept
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	constexpr JFVector4& JFVector4::operator/=(const JFVector4& v) noexcept
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	inline float JFVector4::Length() const noexcept
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	constexpr float JFVector4::LengthSq() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	constexpr JFVector4& JFVector4::Normalize() noexcept
	{
		float lenSq = x * x + y * y + z * z + w * w;
		if (lenSq > 0.0f)
		{
			float lenInv = 1.0f / sqrtf(lenSq);
			x *= lenInv;
			y *= lenInv;
			z *= lenInv;
			w *= lenInv;
		}
		return *this;
	}

	constexpr bool JFVector4::IsNan() const noexcept
	{
		return !(x == x && y == y && z == z && w == w);
	}

	constexpr bool JFVector4::IsNearZero(float toleranceSqrt) const noexcept
	{
		return LengthSq() <= toleranceSqrt;
	}

	constexpr bool JFVector4::IsNormalized(float tolerance) const noexcept
	{
		return Abs(LengthSq() - 1.0f) <= tolerance;
	}
}