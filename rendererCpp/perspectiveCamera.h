#pragma once
#include "orthogonalCamera.h"

class perspectiveCamera :public orthogonalCamera
{
public:
	perspectiveCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender, float distanceToEyepoint);
	perspectiveCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender, float distanceToEyepoint);

protected:
	float d;
	vector3 eyePoint;
	ray constructPerspectiveRay(float x, float y);
	vector3 antiAliase(float x, float y, float squareSize);
};

