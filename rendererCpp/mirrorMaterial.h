#pragma once
#include "material.h"
class mirrorMaterial :
	public material
{
public:
	mirrorMaterial();
	~mirrorMaterial();

	vector3 shade(rayHitInfo &info);
};

