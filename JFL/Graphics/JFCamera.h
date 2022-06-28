//
//  File: JFCamera.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Math/JFMath.h"

namespace JFL
{
	class JFL_API JFCamera final
	{
	public:
		JFCamera();
		~JFCamera() = default;

		void SetupViewMatrix(const JFVector3& pos, const JFVector3& targetPos, const JFVector3& worldUp);

		void SetPerspective(float vFov, float aspect, float nearZ, float farZ);  // use reversed-Z, Depth clear should be zero.
		void SetOrthographics(float width, float height, float nearZ, float farZ);
		bool IsPerspective() const;
		bool IsOrthographic() const;

		float NearZ() const { return nearZ; }
		float FarZ() const { return farZ; }
		JFVector3 Position() const;
		JFMatrix4 ViewMatrix() const;
		JFMatrix4 ProjectionMatrix() const;

	private:
		float nearZ;
		float farZ;
		JFMatrix4 viewMatrix;
		JFMatrix4 projectionMatrix;
	};
}
