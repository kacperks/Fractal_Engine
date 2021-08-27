#pragma once

#include "pch.h"

#include "Collider.h"

namespace fr::Physics {
	class AABB {
	public:
		AABB(Vec3 minExtents, Vec3 maxExtents) : _minExtents(minExtents), _maxExtents(maxExtents) {}

		IntersectData IntersectAABB(AABB other);
		Vec3 GetMinExtents() { return _minExtents; }
		Vec3 GetMaxExtents() { return _maxExtents; }
		static void Test();
	private:
		Vec3 _minExtents;
		Vec3 _maxExtents;
	};
}