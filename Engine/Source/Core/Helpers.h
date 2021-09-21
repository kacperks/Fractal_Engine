#pragma once

#include "Math/Math.h"
#include "pch.h"

namespace fr::helpers {
    glm::vec2 vec2_fr2glm(Vec2 v) { return glm::vec2(v.x, v.y); }
    glm::vec3 vec3_fr2glm(Vec3 v) { return glm::vec3(v.x, v.y, v.z); }
    glm::vec4 vec4_fr2glm(Vec4 v) { return glm::vec4(v.x, v.y, v.z, v.w); }
}