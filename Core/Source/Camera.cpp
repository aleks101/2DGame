#include "Camera.h"

Camera::Camera() {
	cameraPos = NULL;
}
void Camera::Init(SDL_Rect* _cameraPos) {
	cameraPos = _cameraPos;
	prevCamera = *cameraPos;
}
void Camera::SetCamera() {
	prevXoffset = cameraPos->x - prevCamera.x;
	prevYoffset = cameraPos->y - prevCamera.y;

	prevCamera = *cameraPos;
}
bool Camera::CheckForChange() {
	if (prevXoffset != 0 || prevYoffset != 0) {
		return true;
	}
	return false;
}
Vec2 Camera::CalculateChange() {
	//if player's position gets below x0 and y0, camera stops working properly
	int xOffset, yOffset;

	xOffset = -prevXoffset;
	yOffset = -prevYoffset;

	return Vec2(xOffset, yOffset);
}