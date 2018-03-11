#pragma once
#include "ambientLight.h"
#include "light.h"
#include "geometricObject.h"

class world
{
public:
	world();
	world(int maxAntialiasingIterations, int minColorDistance);
	world(int maxAntialiasingIterations, int minColorDistance, ambientLight ambientToSet);

	void addObject(geometricObject *objectToAdd);
	void addLight(light *lightToAdd);
	void setAmbientLight(ambientLight lightToSet);
	void setRefractionIndex(float index);
	vector3 getAmbientLight();

	int maxAntialiasingIterations; //g��boko�� rekurencji algorytmu AA
	int minColorDistanceSquare; //zmienna u�ywana do okre�lania maksymalnego dystansu mi�dzy kolorami, kt�ra odpala AA
	float indexOfRefraction; //index of refracion for the default substance in the world
	ambientLight currentAmbientLight;
	vector<geometricObject*> objectsInTheScene;
	vector<light*> lightsInTheScene;
};

