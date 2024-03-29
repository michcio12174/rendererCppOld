#include "stdafx.h"
#include "world.h"

world::world()
{
	this->currentAmbientLight = ambientLight(vector3(1, 1, 1), 0.1);
	indexOfRefraction = 1;
}

world::world(ambientLight ambientToSet)
{
	this->currentAmbientLight = ambientLight(ambientToSet);
	indexOfRefraction = 1;
}

void world::addObject(geometricObject *objectToAdd)
{
	objectsInTheScene.push_back(objectToAdd);
}

void world::addLight(light * lightToAdd)
{
	lightsInTheScene.push_back(lightToAdd);
}

void world::setAmbientLight(ambientLight lightToSet) 
{
	this->currentAmbientLight = lightToSet;
}

void world::setRefractionIndex(float index)
{
	indexOfRefraction = index;
}

vector3 world::getAmbientLight()
{
	return currentAmbientLight.getLight();
}
