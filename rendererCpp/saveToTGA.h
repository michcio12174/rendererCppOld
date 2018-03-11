#pragma once

#include "buffer.h"

class saveToTGA
{
public:
	saveToTGA();
	~saveToTGA();

	static bool saveImage(int width, int height, vector4 *buffer);
	static bool saveImage(int width, int height, vector3 *buffer);
	static bool saveImage(buffer& bufferInstance);
private:
	static bool saveToFile(int width, int height, int* buffer, string name);
};

