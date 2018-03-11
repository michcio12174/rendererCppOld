#include "stdafx.h"
#include "specularMaterial.h"
#include "multipleObjectsTracer.h"


specularMaterial::specularMaterial():
	material()
{
	this->highlightIntensity = 0.5;
	this->highlightSize = 100;
}

specularMaterial::specularMaterial(texture * materialTexture, float highlightIntensity, float highlightSize):
	material(materialTexture)
{
	this->highlightIntensity = highlightIntensity;
	this->highlightSize = highlightSize;
}


specularMaterial::~specularMaterial()
{
}

vector3 specularMaterial::shade(rayHitInfo & info)
{
	ray rayToLightSource;

	vector3 pixelColor(0, 0, 0);

	//get color from ambient light
	pixelColor = info.worldToRender->currentAmbientLight.getLight() * getTextureColor(info.hitPoint);

	//liczê dla ka¿dego œwiat³a w œwiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); i++) {
		//find ray to light surce
		vector3 intersectionPoint = info.incomingRay.origin + info.incomingRay.direction*info.t;
		intersectionPoint = intersectionPoint + info.normal*shadowBias;
		vector3 directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		directionToLight.normalize();
		rayHitInfo tempInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits source
		multipleObjectsTracer::traceShadowRay(tempInfo, info.worldToRender->lightsInTheScene[i]);
		//liczymy tylko wartoœæ rozb³ysku zale¿nego od koloru œwiat³a
		//w ten sposób mo¿na go zsumowaæ w klasach dziedizcz¹cych z tej (dodaæ do diffuse w Phongu)
		//kolor materia³u dla materia³u tylko specularowego jest dodawany w funkcji shade powy¿ej
		if (!tempInfo.hitOccured) {
			vector3 reflectionVector = -directionToLight - info.normal * (info.normal.dot(-directionToLight) * 2);
			float RdotV = max(0.0f, (-info.incomingRay.direction).dot(reflectionVector));
			pixelColor = pixelColor + info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * (highlightIntensity * pow(RdotV, highlightSize));
		}
	}
	return pixelColor;
}