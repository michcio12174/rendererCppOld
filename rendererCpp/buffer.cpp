#include "stdafx.h"
#include "buffer.h"

vector3 white(1, 1, 1);

buffer::buffer(int width, int height):
	width(width),
	height(height),
	length(width*height),
	colorBuffer(new vector3[length]),
	depthBuffer(new float[length])
{
	clear();
}

void buffer::clear()
{
	for (int i = 0; i < length; i++) {
		colorBuffer[i] = white;
		depthBuffer[i] = 1.0f;
	}
}

void buffer::clearColor()
{
	for (int i = 0; i < length; i++) {
		colorBuffer[i] = white;
	}
}

void buffer::clearDepth()
{
	for (int i = 0; i < length; i++) {
		depthBuffer[i] = 1.0f;
	}
}

void buffer::write(int x, int y, vector3 colorToWrite, float depth)
{
	colorBuffer[x + y *width] = colorToWrite;//TO OPT liczenie pozycji
	depthBuffer[x + y *width] = depth;
}

void buffer::fillBufferWithColor(vector3 fillColor)
{
	for (int i = 0; i < length; i++) {
		colorBuffer[i] = fillColor;
	}
}

float buffer::getDepth(int x, int y)
{
	return depthBuffer[x + y * width];
}

void buffer::displayImages()
{
	CImg<unsigned char> renderedImage = CImg<unsigned char>(width, height, 1, 3, 0);
	CImg<unsigned char> bufferImage = CImg<unsigned char>(width, height, 1, 3, 0);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			vector3 tempColor = colorBuffer[i + length - (j + 1)*width];
			tempColor.toEightBit();

			renderedImage(i, j, 0) = tempColor.r;
			renderedImage(i, j, 1) = tempColor.g;
			renderedImage(i, j, 2) = tempColor.b;

			float tempDepth = depthBuffer[i + length - (j + 1)*width];//todo czemu tu odwracam a gdzie indziej nie
			vector3 tempDepthColor(tempDepth, tempDepth, tempDepth);
			tempDepthColor.toEightBit(); //todo co tu siê dzieje

			bufferImage(i, j, 0) = tempDepthColor.r;
			bufferImage(i, j, 1) = tempDepthColor.g;
			bufferImage(i, j, 2) = tempDepthColor.b;
		}
	}

	CImgDisplay windowImage(renderedImage, "Image");
	CImgDisplay windowDepth(bufferImage, "Depth");

	while (!windowImage.is_closed() && !windowDepth.is_closed()) {
		windowImage.wait();
	}
}
