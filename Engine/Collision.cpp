#include "Collision.h"

namespace coll {
	bool CheckCollisionAABB(SDL_Rect A, SDL_Rect B) {
		int leftA = A.x;
		int rightA = A.x + A.w;
		int topA = A.y;
		int bottomA = A.y + A.h;

		int leftB = B.x;
		int rightB = B.x + B.w;
		int topB = B.y;
		int bottomB = B.y + B.h;

		if (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB) {
			return true;
		}
		return false;
	}
    bool CheckCollisionY(SDL_Rect A, SDL_Rect B) {
        int leftA = A.x;
        int rightA = A.x + A.w;
        int topA = A.y;
        int bottomA = A.y + A.h;

        int leftB = B.x;
        int rightB = B.x + B.w;
        int topB = B.y;
        int bottomB = B.y + B.h;

        if (topA >= topB && topA <= bottomB) {
            return true;
        }
        else if (bottomA >= topB && bottomA < bottomB) {
            return true;
        }
        return false;
    }
    bool CheckCollisionX(SDL_Rect A, SDL_Rect B) {
        int leftA = A.x;
        int rightA = A.x + A.w;
        int topA = A.y;
        int bottomA = A.y + A.h;

        int leftB = B.x;
        int rightB = B.x + B.w;
        int topB = B.y;
        int bottomB = B.y + B.h;

        if (rightA >= leftB && leftA < leftB) {
            return true;
        }
        else if (leftA <= rightB && rightA > rightB) {
            return true;
        }

        return false;
    }
}