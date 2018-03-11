#pragma once
#include "world.h"

class orthogonalCamera
{
public:
	orthogonalCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender);
	orthogonalCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender);

	void setZoom(float zoom);
	void setResolution(int width, int height);
	virtual CImg<unsigned char> renderImage();

protected:
	int width, height;
	float pixelSize;
	vector3 u, v, w, up;
	vector3 planeCenter, lookat;
	world* worldToRender;

	virtual vector3 antiAliase(float x, float y, int iteration, float squareSize);
	vector3 pointToGlobal(vector3 point);
	vector3 vectorToGlobal(vector3 vector);
	ray rayToGlobal(ray localRay);
	void computeUVW(vector3 &planeCenter, vector3 &lookat, vector3 &up);
};

