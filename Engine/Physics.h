#pragma once

#include <iostream>
#include <math.h>
#include "Vec2.h"

namespace physics {
	Vec2 CalculateVelocity(Vec2 currentPos, Vec2 targetPos, float constantVelocity);
	Vec2 calculateVelocityProportional(const Vec2& currentPosition, const Vec2& targetPosition, float constantVelocity);
}