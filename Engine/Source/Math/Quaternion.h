#pragma once

#include "pch.h"
#include "Math.h"
#include "Vector4.h"
#include "Matrix4.h"


namespace fr::Math {
	class Quaternion : public Vec4 {
	public:
		Quaternion(Mat4& m);
		Quaternion(Vec4& m);
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vec3& axis, float angle);

		Quaternion sLerp(const Quaternion& q, float lf, bool sp);
		Quaternion nLerp(const Quaternion& q, float lf, bool sp);

		Mat4 ToRotMatrix();

		Vec3 GetForward();
		Vec3 GetBack();
		Vec3 GetDown();
		Vec3 GetLeft();
		Vec3 GetRight();
	};
}
