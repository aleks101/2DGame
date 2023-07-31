#include "Physics.h"

namespace physics {
	Vec2 CalculateVelocity(Vec2 currentPos, Vec2 targetPos, float constantVelocity) {
		if (currentPos != targetPos) {
			// Calculate the direction vector from current position to target position
			float dx = targetPos.x - currentPos.x;
			float dy = targetPos.y - currentPos.y;

			// Calculate the distance between current position and target position
			float distance = std::sqrt(dx * dx + dy * dy);

			// Calculate the time needed to reach the target position
			float time = distance / constantVelocity;

			// Calculate the required velocity on both x and y coordinates
			Vec2 velocity;
			velocity.x = dx / time;
			velocity.y = dy / time;

			return velocity;
		}
		return Vec2(1, 1);
	}
	Vec2 calculateVelocityProportional(const Vec2& currentPosition, const Vec2& targetPosition, float constantVelocity) {
		if (currentPosition != targetPosition) {
			// Calculate the direction vector from current position to target position
			float dx = targetPosition.x - currentPosition.x;
			float dy = targetPosition.y - currentPosition.y;

			// Calculate the distance between current position and target position
			float distance = std::sqrt(dx * dx + dy * dy);

			// Calculate the time needed to reach the target position based on the largest component of velocity
			float time = distance / constantVelocity;
			if (std::abs(dx) > std::abs(dy)) {
				time = std::abs(dx) / constantVelocity;
			}
			else {
				time = std::abs(dy) / constantVelocity;
			}

			// Calculate the required velocity on both x and y coordinates
			Vec2 velocity;
			velocity.x = dx / time;
			velocity.y = dy / time;

			return velocity;
		}
		return Vec2(1, 1);
	}
}