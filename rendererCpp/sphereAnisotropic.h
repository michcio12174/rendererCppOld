#pragma once
#include "sphere.h"
//wersja sfery zwracaj�ca odbicia anizotropiczne
class sphereAnisotropic :
	public sphere
{
public:
	sphereAnisotropic();
	sphereAnisotropic(vector3 origin, float radius, material *materialToUse, vector3 anisotropyVector);
	sphereAnisotropic(const sphereAnisotropic &sphere);
	~sphereAnisotropic();

	bool hit(rayHitInfo &info);

private:
	vector3 anisotropyVector;
};

