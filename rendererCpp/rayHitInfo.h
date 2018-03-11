#pragma once
#include "ray.h"

class world;
class material;

struct rayHitInfo
{
	rayHitInfo();
	rayHitInfo(ray &incomingRay, world *worldToRender);
	rayHitInfo(ray &incomingRay, world *worldToRender, int reflectionNr);
	
	bool hitOccured;
	int reflectionNr; //parameter says which reflection the ray represents; stops infinite reflections
	float t;
	vector3 normal;
	vector3 hitPoint;
	vector3 sphericalAnisotropicVector;
	ray incomingRay;
	world *worldToRender;
	material *materialToShade;

	static float minIntersectionDistance; //distance used do avoid errors during intersections

	void setHit(float &t, vector3 &normal, material *materialToShade, vector3 hitPoint);
	void setHitAnisotropicSphere(float &t, vector3 &normal, material *materialToShade, vector3 hitPoint, vector3 anisotropicVector);
	vector3 globalHitPoint();
	void operator = (rayHitInfo &info);
};

