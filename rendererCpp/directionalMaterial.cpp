#include "stdafx.h"
#include "directionalMaterial.h"


directionalMaterial::directionalMaterial(): material()
{
}

directionalMaterial::directionalMaterial(texture * materialTexture) :material(materialTexture)
{
}

directionalMaterial::~directionalMaterial()
{
}

vector3 directionalMaterial::shade(rayHitInfo & info)
{
	float temp = info.normal.dot(-info.incomingRay.direction);
	return getTextureColor(info.hitPoint)*temp;
}