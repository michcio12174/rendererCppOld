#include "stdafx.h"
#include "diffuseMaterial.h"
#include "multipleObjectsTracer.h"

diffuseMaterial::diffuseMaterial() : material()
{
}

diffuseMaterial::diffuseMaterial(texture * materialTexture, float diffuseCoefficient) : material(materialTexture)
{
	this->diffuseCoefficient = diffuseCoefficient;
}


diffuseMaterial::~diffuseMaterial()
{
}

vector3 diffuseMaterial::shade(rayHitInfo &info)
{
	ray rayToLightSource;

	vector3 pixelColor(0, 0, 0);

	//get color from ambient
	pixelColor = info.worldToRender->currentAmbientLight.getLight() * getTextureColor(info.hitPoint);

	//licz� dla ka�dego �wiat�a w �wiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); i++) {
		//find ray to light surce
		vector3 intersectionPoint = info.incomingRay.origin + info.incomingRay.direction*info.t;
		intersectionPoint = intersectionPoint + info.normal*shadowBias;
		vector3 directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		directionToLight.normalize();
		rayHitInfo tempInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits source
		multipleObjectsTracer::traceShadowRay(tempInfo, info.worldToRender->lightsInTheScene[i]);
		//kolor materia�u razy kolor �wiat�a w zale�no�ci od k�ta padania �wiat�a
		if (!tempInfo.hitOccured) {
			float dot = max(0.0f, info.normal.dot(directionToLight));
			pixelColor = pixelColor + getTextureColor(info.hitPoint) * dot * info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * diffuseCoefficient;
		}
	}
	return pixelColor;
}
