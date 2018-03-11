#pragma once
#include "material.h"

class specularMaterial :
	public virtual material
{
public:
	specularMaterial();
	specularMaterial(texture *materialTexture, float highlightIntensity, float highlightSize);
	~specularMaterial();

	vector3 shade(rayHitInfo &info);
private:
	float highlightSize;
	float highlightIntensity;
};

