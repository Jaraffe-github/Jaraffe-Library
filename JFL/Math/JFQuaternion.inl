//
//  File: JFQuaternion.inl
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFQuaternion.h"
#include "JFVector3.h"

namespace JFL
{
	constexpr JFQuaternion::JFQuaternion() noexcept
		: x(0.f)
		, y(0.f)
		, z(0.f)
		, w(0.f)
	{}

	constexpr JFQuaternion::JFQuaternion(float x, float y, float z, float w) noexcept
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{}

	inline JFQuaternion::JFQuaternion(float pitch, float yaw, float roll) noexcept
	{
		float sinPitch = std::sinf(pitch);
		float cosPitch = std::cosf(pitch);
		float sinYaw = std::sinf(yaw);
		float cosYaw = std::cosf(yaw);
		float sinRoll = std::sinf(roll);
		float cosRoll = std::cosf(roll);
		
		x = sinPitch * sinYaw * sinRoll + cosPitch * cosYaw * cosRoll;
		y = cosPitch * sinYaw * sinRoll + sinPitch * cosYaw * cosRoll;
		z = cosPitch * sinYaw * cosRoll - sinPitch * cosYaw * sinRoll;
		w = sinPitch * -sinYaw * cosRoll + cosPitch * cosYaw * sinRoll;
	}

	inline JFQuaternion::JFQuaternion(const JFVector3& axis, float angle) noexcept
	{
		float sin = std::sinf(angle);
		x = sin * axis.x;
		y = sin * axis.y;
		z = sin * axis.z;
		w = std::cosf(angle);
	}

	inline constexpr float JFQuaternion::Dot(const JFQuaternion& q1, const JFQuaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	inline constexpr JFQuaternion JFQuaternion::Slerp(const JFQuaternion& q1, const JFQuaternion& q2, float t)
	{
		float signScale = 1.f;
		float dot = JFQuaternion::Dot(q1, q2);

		// Adjust signs
		if (dot < 0.f)
		{
			dot = -dot;
			signScale = -1.f;
		}

		float scale1 = 1.f;
		float scale2 = 0.f;
		// Quaternions are very close so we can do a linear interpolation
		if (1.f - dot > 0.0001f)
		{
			scale1 = 1.f - t;
			scale2 = signScale * t;
		}
		// Standard case (slerp)
		else
		{
			float theta = std::acosf(dot);
			float sinInv = 1.f / std::sinf(theta);
			scale1 = std::sinf((1.f - t) * theta) * sinInv;
			scale2 = signScale * std::sinf(t * theta) * sinInv;
		}

		return JFQuaternion(
			scale1 * q1.x + scale2 * q2.x,
			scale1 * q1.y + scale2 * q2.y,
			scale1 * q1.z + scale2 * q2.z,
			scale1 * q1.w + scale2 * q2.w
		).Normalize();
	}

	inline constexpr JFQuaternion JFQuaternion::operator+(const JFQuaternion& q) const noexcept
	{
		return JFQuaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	inline constexpr JFQuaternion JFQuaternion::operator*(const JFQuaternion& q) const noexcept
	{
		return JFQuaternion(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x,
			w * q.w - x * q.x - y * q.y - z * q.z
		);
	}

	inline constexpr JFQuaternion& JFQuaternion::operator+=(const JFQuaternion& q) noexcept
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}

	inline constexpr JFQuaternion& JFQuaternion::operator*=(const JFQuaternion& q) noexcept
	{
		JFQuaternion quat = *this;
		x = quat.w * q.x + quat.x * q.w + quat.y * q.z - quat.z * q.y;
		y = quat.w * q.y + quat.y * q.w + quat.z * q.x - quat.x * q.z;
		z = quat.w * q.z + quat.z * q.w + quat.x * q.y - quat.y * q.x;
		w = quat.w * q.w - quat.x * q.x - quat.y * q.y - quat.z * q.z;
		return *this;
	}

	inline constexpr JFVector3 JFQuaternion::Euler() const
	{
		return JFVector3(
			std::atan2f(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y)),	// x
			Clamp(2.f * (w * y + y * z), -1.f, 1.f),							// y
			std::atan2f(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z))		// z
		);
	}

	inline float JFQuaternion::Length() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}

	inline constexpr float JFQuaternion::LengthSq() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	inline constexpr JFQuaternion& JFQuaternion::Inverse() noexcept
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline constexpr JFQuaternion& JFQuaternion::Normalize() noexcept
	{
		const float lenSq = x * x + y * y + z * z + w * w;
		if (lenSq > 0.f)
		{
			float lenInv = 1.0f / std::sqrtf(lenSq);
			x *= lenInv;
			y *= lenInv;
			z *= lenInv;
			w *= lenInv;
		}
		return *this;
	}

	inline constexpr bool JFQuaternion::IsUnitQuaternion(float tolerance) const noexcept
	{
		return Abs(LengthSq() - 1.0f) <= tolerance;
	}
}
