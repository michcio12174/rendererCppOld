#pragma once

#include "buffer.h"
#include "mesh.h"
#include "vertexProcessor.h"
#include "saveToTGA.h"
#include "OBJReader.h"

class rasterizer
{
public:
	rasterizer(int width, int height);

	//rasterization
	void drawTriangle(triangle triangle);
	void drawMesh(mesh meshToDraw); //TO OPT
	void render();
	void addObject(mesh meshToDraw); //TO OPT
	void saveToTGA();
	//adding lights
	void setAmbientLight(ambientLight l);
	void addLight(light l);
	//setting vertex processor properties
	void setPerspective(float fov, float aspect, float nearPlane_z, float farPlane_z);
	void setLookAt(vector3 eye, vector3 target, vector3 up);
	void calculateFinalTransformMatrix();
	//other
	void displayImages();

private:
	unique_ptr<buffer> bufferInstance;
	unique_ptr<vertexProcessor> VPInscance;
	vector <mesh> objectsInTheScene;
};

