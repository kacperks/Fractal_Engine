#pragma once

#include "Math/Vector3.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

#define FR_PHYSICS_COLLIDER_TYPE_SPHERE 0
#define FR_PHYSICS_COLLIDER_TYPE_PLANE 1
#define FR_PHYSICS_COLLIDER_TYPE_SIZE 2

namespace fr::Physics {
	struct CollisionPoints {
		CollisionPoints() = default;
		~CollisionPoints() = default;

		Vec3 A;
		Vec3 B;
		Vec3 Normal = A.Normalized() + B.Normalized();
		float Depth = A.Lenght() + B.Lenght();
		bool HasCollision;
	};

	class IntersectData
	{
	public:
		IntersectData(const bool doesIntersect, const Vec3& direction) : _doesIntersect(doesIntersect), _direction(direction) {}
		inline bool GetDoesIntersect() { return _doesIntersect; }
		inline float GetDistance() { return _direction.Lenght(); }
		inline const Vec3& GetDirection() { return _direction; }
	private:
		bool  _doesIntersect;
		Vec3 _direction;
	};


	class Collider
	{
		public:	
			
		enum {
			TYPE_SPHERE,
			TYPE_AABB,
			TYPE_SIZE
		};

		Collider(int type) : _type(type) {}
		IntersectData Intersect(const Collider& other) const;
		virtual void Transform(const Vec3& translation) {}
		virtual Vec3 GetCenter() const { return Vec3(); }
		inline int GetType() const { return _type; }
	private:
		int _type;
	};
}