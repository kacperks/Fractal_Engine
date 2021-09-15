#include "pch.h"

#include "aabb.h"

namespace fr::Physics {
	IntersectData AABB::IntersectAABB(AABB other){
		Math::Vec3 distances1 = other.GetMinExtents() - max;
		Math::Vec3 distances2 = min - other.GetMaxExtents();
		Math::Vec3 distances = Math::Vec3(distances1.Max(distances2));
		float maxDistance = distances.Max();
		return IntersectData(maxDistance < 0, distances);
	}

	void AABB::Test()
	{
		AABB aabb1(Math::Vec3(0.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 1.0f));
		AABB aabb2(Math::Vec3(1.0f, 1.0f, 1.0f), Math::Vec3(2.0f, 2.0f, 2.0f));
		AABB aabb3(Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(2.0f, 1.0f, 1.0f));
		AABB aabb4(Math::Vec3(0.0f, 0.0f, -2.0f), Math::Vec3(1.0f, 1.0f, -1.0f));
		AABB aabb5(Math::Vec3(0.0f, 0.5f, 0.0f), Math::Vec3(1.0f, 1.5f, 1.0f));
		AABB aabb6(Math::Vec3(0.3f, 0.5f, 0.7f), Math::Vec3(1.3f, 1.5f, 1.7f));

		IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
		IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
		IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
		IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);
		IntersectData aabb1Intersectaabb6 = aabb1.IntersectAABB(aabb6);

		assert(aabb1Intersectaabb2.GetDoesIntersect() == false);
		assert(aabb1Intersectaabb3.GetDoesIntersect() == false);
		assert(aabb1Intersectaabb4.GetDoesIntersect() == false);
		assert(aabb1Intersectaabb5.GetDoesIntersect() == true);
		assert(aabb1Intersectaabb6.GetDoesIntersect() == true);
	}
}