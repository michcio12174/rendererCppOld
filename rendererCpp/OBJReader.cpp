#include "stdafx.h"
#include "OBJReader.h"

OBJReader::OBJReader(mesh & meshToLoad, const string & fileName, const float & scale):
	meshPointer(&meshToLoad)
{
	LoadMesh(fileName, scale);
}

void OBJReader::LoadMesh(const string & fileName, const float & scale)
{
	string token;
	string stringValue;
	ifstream objFile(fileName + ".obj");
	ifstream mtlFile(fileName + ".mtl");

	vector3 vectorValue;
	char delimeter = ' ';
	vector<string> objFileTokens;
	vector<string> mtlFileTokens;

	if (mtlFile.is_open())
	{
		while (mtlFile >> token)
		{
			mtlFileTokens.push_back(token);
		}

		mtlFile.close();
	}
	else
	{
		cout << "Unable to open file: " << fileName << ".mtl" << endl;
	}

	if (objFile.is_open())
	{
		while (objFile >> token)
		{
			objFileTokens.push_back(token);
		}

		objFile.close();
	}
	else
	{
		cout << "Unable to open file: " << fileName << ".obj" << endl;
	}

	//------------------------------loading materials from .mat------------------------------

	materialR *currentMat = new materialR();
	size_t count = mtlFileTokens.size();
	int i = 0;
	while (i < count)
	{
		if (mtlFileTokens[i] == "newmtl")
		{
			meshPointer->materials.push_back(materialR(mtlFileTokens[i + 1], currentMat->typeOfMaterial, currentMat->n));
			currentMat = &meshPointer->materials[meshPointer->materials.size() - 1];
			i += 2;
			continue;
		}

		if (mtlFileTokens[i] == "Ns")
		{
			currentMat->ns = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Ni")
		{
			currentMat->ni = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "d")
		{
			currentMat->d = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Tr")
		{
			currentMat->tr = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Tf")
		{
			currentMat->tf = vector3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]));
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "illum")
		{
			currentMat->illum = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Ka")
		{
			currentMat->colorAmbient = vector3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]));
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Kd")
		{
			currentMat->colorDiffuse = vector3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]));
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Ks")
		{
			currentMat->colorSpecular = vector3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]));
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Ke")
		{
			currentMat->colorEmissive = vector3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]));
			i += 4;
			continue;
		}

		//TEXTURES
		/*if (mtlFileTokens[i] == "map_Ka")
		{
			currentMat->ambientTexture = texture(mtlFileTokens[i + 1], true);
			i += 2;
		}
		if (mtlFileTokens[i] == "map_Kd")
		{
			currentMat->diffuseTexture = texture(mtlFileTokens[i + 1], true);
			i += 2;
		}*/
		//if (mtlFileTokens[i] == "map_Ks")
		//{
		//    currentMat->SpecularTexture(Texture(512, 512, mtlFileTokens[i + 1]));
		//    i += 2;
		//}


		++i;
	}

	//------------------------------loading geometry from .obj------------------------------
	count = objFileTokens.size();
	i = 0;

	while (i < count)
	{
		if (objFileTokens[i] == "v")
		{
			vertices.push_back(vector3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
			i += 4;
			continue;
		}

		if (objFileTokens[i] == "vn")
		{
			normals.push_back(vector3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
			i += 4;
			continue;
		}

		if (objFileTokens[i] == "vt")
		{
			textureCoord.push_back(vector3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
			i += 4;
			continue;
		}

		if (objFileTokens[i] == "usemtl")
		{
			for (materialR &mat : meshPointer->materials)
			{
				if (mat.name == objFileTokens[i + 1])
				{
					currentMat = &mat;
				}
			}
		}

		if (objFileTokens[i] == "f")
		{
			size_t first = objFileTokens[i + 1].find_first_of('/');
			size_t last = objFileTokens[i + 1].find_last_of('/');

			string sub = objFileTokens[i + 1].substr(0, first);
			int index1 = stoi(sub) - 1;

			first = objFileTokens[i + 2].find_first_of('/');
			sub = objFileTokens[i + 2].substr(0, first);
			int index2 = stoi(sub) - 1;

			first = objFileTokens[i + 3].find_first_of('/');
			sub = objFileTokens[i + 3].substr(0, first);
			int index3 = stoi(sub) - 1;

			sub = objFileTokens[i + 1].substr(++last, objFileTokens[i + 1].size());
			int index4 = stoi(sub) - 1;

			first = objFileTokens[i + 1].find_first_of('/');
			last = objFileTokens[i + 1].find_last_of('/');
			sub = objFileTokens[i + 1].substr(++first, last);
			int index5 = stoi(sub) - 1;

			first = objFileTokens[i + 2].find_first_of('/');
			last = objFileTokens[i + 2].find_last_of('/');
			sub = objFileTokens[i + 2].substr(++first, last);
			int index6 = stoi(sub) - 1;

			first = objFileTokens[i + 3].find_first_of('/');
			last = objFileTokens[i + 3].find_last_of('/');
			sub = objFileTokens[i + 3].substr(++first, last);
			int index7 = stoi(sub) - 1;
			
			meshPointer->triangles.push_back(triangle(
				vertex(vertices[index2], normals[index4], textureCoord[index5]),
				vertex(vertices[index1], normals[index4], textureCoord[index6]),
				vertex(vertices[index3], normals[index4], textureCoord[index7])
				));
			i += 4;
			continue;
		}

		++i;
	}

	//------------------------------finding the center of object------------------------------
	float minX = 0.0f, minY = 0.0f, minZ = 0.0f, maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;

	for (auto &vertex : vertices)
	{
		if (vertex.x < minX)
		{
			minX = vertex.x;
		}

		if (vertex.y < minY)
		{
			minY = vertex.y;
		}

		if (vertex.z < minZ)
		{
			minZ = vertex.z;
		}

		if (vertex.x > maxX)
		{
			maxX = vertex.x;
		}

		if (vertex.y > maxY)
		{
			maxY = vertex.y;
		}

		if (vertex.z > maxZ)
		{
			maxZ = vertex.z;
		}
	}

	float halfX = (maxX - minX) * 0.5f;
	float halfY = (maxY - minY) * 0.5f;
	float halfZ = (maxZ - minZ) * 0.5f;

	meshPointer->center = vector3(minX + halfX, minY + halfY, minZ + halfZ);

	cout << "mesh center printed from OBJReader: " << meshPointer->center.toString() << endl;

	/*float radius = 0.0f; //to chyba nic nie robi
	float distance = 0.0f;
	for (auto &vertex : vertices)
	{
		distance = sqrt(vertex.distanceSquare(meshPointer->center));
		if (distance > radius)
		{
			radius = distance;
		}
	}*/
}
