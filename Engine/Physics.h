#pragma once

#include <iostream>
#include <math.h>
#include "Vec2.h"

namespace physics {
	Vec2 calculateVelocity(Vec2 currentPos, Vec2 targetPos, float constantVelocity);
}