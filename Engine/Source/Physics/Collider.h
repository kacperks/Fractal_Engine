#pragma once

#include "Math/Vector3.h"

#define FR_PHYSICS_COLLIDER_TYPE_SPHERE 0
#define FR_PHYSICS_COLLIDER_TYPE_PLANE 1
#define FR_PHYSICS_COLLIDER_TYPE_SIZE 2

namespace fr::Physics {
	struct CollisionPoints {
		CollisionPoints() = default;
		~CollisionPoints() = default;

		Math::Vec3 A;
		Math::Vec3 B;
		Math::Vec3 Normal = A.Normalized() + B.Normalized();
		float Depth = A.Lenght() + B.Lenght();
		bool HasCollision;
	};

	class IntersectData
	{
	public:
		IntersectData(bool doesIntersect, Math::Vec3 direction) : _doesIntersect(doesIntersect), _direction(direction) {}
		inline bool GetDoesIntersect() { return _doesIntersect; }
		inline float GetDistance() { return _direction.Lenght(); }
		inline const Math::Vec3& GetDirection() { return _direction; }
	private:
		bool  _doesIntersect;
		Math::Vec3 _direction;
	};


	class Collider
	{
		public:	
		Collider() {}
		Collider(int type) : _type(type) {}
		IntersectData Intersect(const Collider& other) const;
		virtual void Transform(const Math::Vec3& translation) {}
		virtual Math::Vec3 GetCenter() const { return Math::Vec3(); }
		inline int GetType() const { return _type; }
	private:
		int _type;
	};
}