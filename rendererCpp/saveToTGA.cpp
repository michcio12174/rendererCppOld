#include "stdafx.h"
#include "saveToTGA.h"


saveToTGA::saveToTGA()
{
}


saveToTGA::~saveToTGA()
{
}

bool saveToTGA::saveImage(int width, int height, vector4 *buffer)
{
	int length = width * height;
	int *intBuffer = new int[length];
	for (int i = 0; i < length; i++) intBuffer[i] = buffer[i].toInt();

	return saveToFile(width, height, intBuffer, "TGAfromVector4");
}

bool saveToTGA::saveImage(int width, int height, vector3 * buffer)
{
	int length = width * height;
	int *intBuffer = new int[length];
	for (int i = 0; i < length; i++) intBuffer[i] = buffer[i].toInt();

	bool result = saveToFile(width, height, intBuffer, "TGAfromVector3");
	delete intBuffer;
	return result;
}

bool saveToTGA::saveImage(buffer& bufferInstance)
{
	int *colorBuffer = new int[bufferInstance.length];
	int *depthBuffer = new int[bufferInstance.length];

	for (int i = 0; i < bufferInstance.length; i++) { 
		colorBuffer[i] = bufferInstance.colorBuffer[i].toInt();
		depthBuffer[i] = vector3(bufferInstance.depthBuffer[i], bufferInstance.depthBuffer[i], bufferInstance.depthBuffer[i]).toInt();
	}

	bool colorResult = saveToFile(bufferInstance.width, bufferInstance.height, colorBuffer, "rasterizerImage");
	bool depthResult = saveToFile(bufferInstance.width, bufferInstance.height, depthBuffer, "rasterizedDepth");
	delete colorBuffer;
	delete depthBuffer;
	return colorResult && depthResult;
}

bool saveToTGA::saveToFile(int width, int height, int* buffer, string name)
{
	string path = "../images/" + name + ".tga";

	unsigned short header[9] = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		width, height,
		0x0820 };

	FILE *f = fopen(path.c_str(), "wb+");
	if (NULL == f) return false;
	else {
		fwrite(header, 2, 9, f);
		fwrite(buffer, 4, width*height, f);
		fclose(f);
		return true;
	}
}
