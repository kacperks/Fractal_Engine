#pragma once

#include "pch.h"

#include "Collider.h"

namespace fr::Physics {
	class AABB {
	public:
		AABB(Math::Vec3 minExtents, Math::Vec3 maxExtents) : min(minExtents), max(maxExtents) {}

		IntersectData IntersectAABB(AABB other);
		Math::Vec3 GetMinExtents() { return min; }
		Math::Vec3 GetMaxExtents() { return max; }
		static void Test();
	private:
		Math::Vec3 min;
		Math::Vec3 max;
	};
}