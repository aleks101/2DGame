#include "Collision.h"

namespace coll {
	bool CheckCollisionAABB(const SDL_Rect* const A, const SDL_Rect* const B) {
		int leftA = A->x;
		int rightA = A->x + A->w;
		int topA = A->y;
		int bottomA = A->y + A->h;

		int leftB = B->x;
		int rightB = B->x + B->w;
		int topB = B->y;
		int bottomB = B->y + B->h;

        if (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB) {
            return true;
        }
        return false;
	}
    bool CheckCollisionX(const SDL_Rect* const A, const SDL_Rect* const B) {
        int leftA = A->x;
        int rightA = A->x + A->w;
        int topA = A->y;
        int bottomA = A->y + A->h;

        int leftB = B->x;
        int rightB = B->x + B->w;
        int topB = B->y;
        int bottomB = B->y + B->h;

        if (rightA > leftB && leftA < leftB) {
            return true;
        }
        else if (leftA < rightB && rightA > rightB) {
            return true;
        }
        return false;
    }
    bool CheckCollisionY(const SDL_Rect* const A, const SDL_Rect* const B) {
        int leftA = A->x;
        int rightA = A->x + A->w;
        int topA = A->y;
        int bottomA = A->y + A->h;

        int leftB = B->x;
        int rightB = B->x + B->w;
        int topB = B->y;
        int bottomB = B->y + B->h;

        if (topA >= topB && topA <= bottomB) {
            return true;
        }
        else if (bottomA >= topB && bottomA < bottomB) {
            return true;
        }
        return false;
                 
    }
}