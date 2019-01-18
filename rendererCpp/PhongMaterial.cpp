#include "stdafx.h"
#include "PhongMaterial.h"
#include "multipleObjectsTracer.h"

PhongMaterial::PhongMaterial()
{
}

PhongMaterial::PhongMaterial(texture * materialTexture, float highlightSize):
	material(materialTexture),
	diffuseCoefficient(1),
	highlightSize(highlightSize),
	highlightIntensity(1)
{
}

PhongMaterial::PhongMaterial(texture * materialTexture, float specularCoefficient, float highlightSize, float diffuseCoefficient):
	material(materialTexture),
	diffuseCoefficient(diffuseCoefficient),
	highlightSize(highlightSize),
	highlightIntensity(specularCoefficient)
{
}

vector3 PhongMaterial::shade(rayHitInfo info)
{
	ray rayToLightSource;

	vector3 pixelColor(0, 0, 0);

	//get color from ambient light
	pixelColor = info.worldToRender->getAmbientLight() * getTextureColor(info.hitPoint);

	//liczê dla ka¿dego œwiat³a w œwiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); i++) {
		//find ray to light surce
		vector3 intersectionPoint = info.globalHitPoint() + info.normal * material::shadowBias;
		vector3 directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		directionToLight.normalize();
		rayHitInfo shadowRayInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits light source
		multipleObjectsTracer::traceShadowRay(shadowRayInfo, info.worldToRender->lightsInTheScene[i]);
		//if intercestion is not in shadow also get color from specular and diffuse shading
		if (!shadowRayInfo.hitOccured) {

			//specular helpers
			vector3 reflectionVector = -directionToLight - info.normal * (info.normal.dot(-directionToLight) * 2);
			float RdotV = max(0.0f, (-info.incomingRay.direction).dot(reflectionVector));

			//diffuse helper
			float dot = max(0.0f, info.normal.dot(directionToLight));

			pixelColor = pixelColor 
				+ info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * (highlightIntensity * pow(RdotV, highlightSize)) //specular component
				+ getTextureColor(info.hitPoint) * dot * info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * diffuseCoefficient; //diffuse component
		}
	}
	return pixelColor;
}