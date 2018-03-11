#include "stdafx.h"
#include "textureSpherical.h"


textureSpherical::textureSpherical() : texture()
{
}

textureSpherical::textureSpherical(string imagePath): 
	texture(imagePath, false)
{
	horizontalRotation = 0;
}

textureSpherical::textureSpherical(string imagePath, int horizontalRotationInDegrees):
	texture(imagePath, false)
{
	if (horizontalRotationInDegrees > 360) horizontalRotationInDegrees = 360;
	if (horizontalRotationInDegrees < 0) horizontalRotationInDegrees = 0;
	horizontalRotation = horizontalRotationInDegrees / 360.0;
}


textureSpherical::~textureSpherical()
{
}

vector3 textureSpherical::getColor(vector3 const &localHitPoint) const
{
	//alfa to k�t w poziomie - w lokalnej p�aszczy�nie xz
	//beta to k�t w pionie - lokalna p�aszczyzna osi y oraz punktu przeci�cia

	float r = localHitPoint.length();
	float alfa = atan2(localHitPoint.x, localHitPoint.z);
	float beta = acos(localHitPoint.y / localHitPoint.length());

	if (alfa < 0) alfa += 2 * 3.14159265359;

	//dodaj� jak�� cz�� 2*pi, �eby obr�ci� tekstur� w poziomie i dbam o to, by nie wyj�� poza przedzia� <0, 2*pi)
	alfa += 6.28318530718 * horizontalRotation;
	if (alfa >= 6.28318530718) alfa -= 6.28318530718;

	float u = alfa * 0.1591549430918953;
	float v = beta / 3.14159265359;

	int x = (width - 1)*u;
	int y = (height - 1)*v;
	
	vector3 textureColor = vector3((*image)(x, y, 0), (*image)(x, y, 1), (*image)(x, y, 2));
	textureColor.scaleToOne();
	return textureColor;
}
