#pragma once

#include "Collider.h"

namespace fr::Physics {
	class BoundingSphere : Collider {
	public:
		BoundingSphere(const Vec3& center, float radius) : _center(center), _radius(radius) {}

		IntersectData IntersectBoundingSphere(const BoundingSphere& other);
		virtual void Transform(const Vec3& translation);
		virtual Vec3 GetCenter() const { return _center; }

		inline float GetRadius() const { return _radius; }

		static void Test();
	private:
		Vec3  _center;
		float _radius;
	};
}