#pragma once
#include "diffuseMaterial.h"
#include "specularMaterial.h"

class PhongMaterial :
	public material
{
public:
	PhongMaterial();
	PhongMaterial(texture *materialTexture, float highlightSize);
	PhongMaterial(texture *materialTexture, float specularCoefficient, float highlightSize, float diffuseCoefficient);

	vector3 shade(rayHitInfo &info);

private:
	float diffuseCoefficient;
	float highlightSize;
	float highlightIntensity;
};

