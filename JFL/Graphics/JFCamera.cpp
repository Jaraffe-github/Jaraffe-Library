//
//  File: JFCamera.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#include "JFCamera.h"

using namespace JFL;

JFCamera::JFCamera()
	: nearZ(0.f)
	, farZ(0.f)
{
}

void JFCamera::SetupViewMatrix(const JFVector3& pos, const JFVector3& targetPos, const JFVector3& worldUp)
{
    JFVector3 forward = (targetPos - pos).Normalize();
    JFVector3 right = JFVector3::Cross(worldUp, forward).Normalize();
    JFVector3 up = JFVector3::Cross(forward, right);

    float x = JFVector3::Dot(-pos, right);
    float y = JFVector3::Dot(-pos, up);
    float z = JFVector3::Dot(-pos, forward);

    this->viewMatrix = {
        right.x, up.x, forward.x, 0.0f,
        right.y, up.y, forward.y, 0.0f,
        right.z, up.z, forward.z, 0.0f,
        x, y, z, 1.0f
    };
}

void JFCamera::SetPerspective(float vFov, float aspect, float nearZ, float farZ)
{
    JFASSERT_DEBUG(vFov > 0);
    JFASSERT_DEBUG(aspect > 0);
    JFASSERT_DEBUG(nearZ > 0);
    JFASSERT_DEBUG(farZ > 0);
    JFASSERT_DEBUG(nearZ < farZ);

    this->nearZ = nearZ;
    this->farZ = farZ;

    // reversed-Z projection matrix
    // it requires clearing Z to 0.0f and using a GREATER variant depth test.
    // ref. https://developer.nvidia.com/content/depth-precision-visualized#:~:text=Reversed-Z%20erases%20the%20distinctions,without%20affecting%20precision%20at%20all.
    float f = 1.0f / tanf(vFov / 2.0f);
    float scale = nearZ / (nearZ - farZ);
    float bias = -farZ * scale;
    this->projectionMatrix = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, scale, 1.0f,
        0.0f, 0.0f, bias, 0.0f
    };
}

void JFCamera::SetOrthographics(float width, float height, float nearZ, float farZ)
{
    JFASSERT_DEBUG(width > 0);
    JFASSERT_DEBUG(height > 0);
    JFASSERT_DEBUG(nearZ > farZ);

    this->nearZ = nearZ;
    this->farZ = farZ;

    float range = 1.0f / (farZ - nearZ);
    this->projectionMatrix = {
        2.0f / width, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / height, 0.0f, 0.0f,
        0.0f, 0.0f, range, 1.0f,
        0.0f, 0.0f, -range * nearZ, 1.0f
    };
}

bool JFCamera::IsPerspective() const
{
	return projectionMatrix._44 == 0.0f;
}

bool JFCamera::IsOrthographic() const
{
	return projectionMatrix._44 == 1.0f;
}

JFVector3 JFCamera::Position() const
{
    return { viewMatrix.m[0][0], viewMatrix.m[0][1], viewMatrix.m[0][2] };
}

JFMatrix4 JFCamera::ViewMatrix() const
{
    return viewMatrix;
}

JFMatrix4 JFCamera::ProjectionMatrix() const
{
    return projectionMatrix;
}
