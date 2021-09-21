#pragma once

#include "pch.h"

#include "Collider.h"

namespace fr::Physics {
	class AABB {
	public:
		AABB(Vec3 minExtents, Vec3 maxExtents) : min(minExtents), max(maxExtents) {}

		IntersectData IntersectAABB(AABB other);
		Vec3 GetMinExtents() { return min; }
		Vec3 GetMaxExtents() { return max; }
		static void Test();
	private:
		Vec3 min;
		Vec3 max;
	};
}