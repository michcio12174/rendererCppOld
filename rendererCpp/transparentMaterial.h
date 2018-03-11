#pragma once
#include "material.h"
class transparentMaterial :
	public material
{
public:
	transparentMaterial();
	transparentMaterial(float indexOfRefraction);
	~transparentMaterial();

	vector3 shade(rayHitInfo & info);

protected:
	double indexOfRefraction;
};

