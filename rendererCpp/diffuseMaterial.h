#pragma once
#include "material.h"

class diffuseMaterial : virtual public material
{
public:
	diffuseMaterial();
	diffuseMaterial(texture *materialTexture, float diffuseCoefficient);
	~diffuseMaterial();

	vector3 shade(rayHitInfo info);
private:
	float diffuseCoefficient;
};

