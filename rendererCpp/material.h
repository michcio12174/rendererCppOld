#pragma once
#include "rayHitInfo.h"
#include "texture.h"
#include "world.h"

class material
{
public:
	material();
	material(texture *materialTexture);
	~material();

	texture *materialTexture;

	virtual vector3 shade(rayHitInfo info);

protected:
	vector3 material::getTextureColor(vector3 localHitPoint) const;
	float shadowBias = 0.0001f;
};

