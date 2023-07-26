#include "Physics.h"

namespace physics {
	Vec2 calculateVelocity(Vec2 currentPos, Vec2 targetPos, float constantVelocity) {
		// Calculate the displacement vector from current position to target position
		Vec2 displacement = { targetPos.m_x - currentPos.m_x, targetPos.m_y - currentPos.m_y };

		// Calculate the distance between current position and target position
		float distance = std::sqrt(displacement.m_x * displacement.m_x + displacement.m_y * displacement.m_y);

		// Calculate the unit vector of the displacement
		Vec2 unitVector = { displacement.m_x / distance, displacement.m_y / distance };

		// Calculate the velocity vector with the given constant magnitude
		Vec2 velocity = { constantVelocity * unitVector.m_x, constantVelocity * unitVector.m_y };

		return velocity;
	}
}