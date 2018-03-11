#pragma once

#include "vectorsAndMatrices.h"

class buffer
{
public:
	buffer(int width, int height);

	//buffer funcions
	void clear();
	void clearColor();
	void clearDepth();
	void write(int x, int y, vector3 colorToWrite, float depth);
	void fillBufferWithColor(vector3 fillColor);
	float getDepth(int x, int y);
	//other
	void displayImages();

	int width, height, length;
	unique_ptr<vector3[]> colorBuffer;
	unique_ptr<float[]> depthBuffer;
};

