#pragma once

#include "mesh.h"

class OBJReader
{
public:
	OBJReader(mesh &meshToLoad, const string &fileName, const float &scale);

private:
	void LoadMesh(const string &fileName, const float &scale);

	mesh *meshPointer;

	vector<vector3> vertices;
	vector<vector3> textureCoord;
	vector<vector3> normals;
};

