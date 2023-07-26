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

	currXoffset = cameraPos->x - prevCamera.x;
	currYoffset = cameraPos->y - prevCamera.y;
}
bool Camera::CheckForChange() {
	if (prevXoffset != currYoffset || prevYoffset != currYoffset) {
		return true;
	}
	return false;
}
Vec2 Camera::CalculateChange() {
	int xOffset, yOffset;
	xOffset = currXoffset - prevXoffset;
	yOffset = currYoffset - prevYoffset;
	return Vec2(xOffset, yOffset);
}