#include "stdafx.h"
#include "orthogonalCamera.h"
#include "multipleObjectsTracer.h"

orthogonalCamera::orthogonalCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender)
{
	//----------obliczam baz� ortonormaln� dla kamery
	computeUVW(planeCenter, lookat, vector3(0, 1, 0, false));
	//----------przypisuj� warto�� pozosta�ym cz�onkom klasy
	this->planeCenter = planeCenter;
	this->lookat = lookat;
	this->worldToRender = worldToRender;
	this->width = 800;
	this->height = 600;
	this->pixelSize = 1 / zoom;
}

orthogonalCamera::orthogonalCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender)
{
	//----------obliczam baz� ortonormaln� dla kamery
	computeUVW(planeCenter, lookat, up);
	//----------przypisuj� warto�� pozosta�ym cz�onkom klasy
	this->planeCenter = planeCenter;
	this->lookat = lookat;
	this->worldToRender = worldToRender;
	this->width = 800;
	this->height = 600;
	this->pixelSize = 1 / zoom;
}

void orthogonalCamera::setZoom(float zoom)
{
	this->pixelSize = 1 / zoom;
}

void orthogonalCamera::setResolution(int width, int height)
{
	this->width = width;
	this->height = height;
}

CImg<unsigned char> orthogonalCamera::renderImage()
{
	CImg<unsigned char> renderedImage = CImg<unsigned char> (width, height, 1, 3, 0);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			//computing local ray origin coordinates
			//nie t�umacz� origina na globalne, bo w antyaliasingu potrzebuj� koordynat�w lokalnych, 
			//�eby wystrzeli� lokalnie przesuni�te promienie
			vector3 returnedColor = antiAliase(
				pixelSize*(width * 0.5f - i + 0.5f),       //x
				pixelSize*(height * 0.5f - j - 0.5f),      //y
				0, pixelSize);

			returnedColor.toEightBit();
			renderedImage(i, j, 0) = returnedColor.r;
			renderedImage(i, j, 1) = returnedColor.g;
			renderedImage(i, j, 2) = returnedColor.b;
		}
	}
	return renderedImage;
}

vector3 orthogonalCamera::antiAliase(float x, float y, int iteration, float squareSize)
{
	squareSize = squareSize / 2;

	ray centerRay(vector3(x, y, 0, false), vector3(0, 0, 1, false)), AARay;
	rayHitInfo info(rayToGlobal(centerRay), worldToRender);
	vector3 centerColor = multipleObjectsTracer::traceRay(info);

	vector3 colors[4];
	for (int i = 0; i < 4; i++) {
		AARay = centerRay;

		switch (i){
		case 0:
			AARay.origin.x -= squareSize;
			AARay.origin.y -= squareSize;
			break;
		case 1:
			AARay.origin.x += squareSize;
			AARay.origin.y -= squareSize;
			break; 
		case 2:
			AARay.origin.x -= squareSize;
			AARay.origin.y += squareSize;
			break; 
		case 3:
			AARay.origin.x += squareSize;
			AARay.origin.y += squareSize;
			break;
		}
		info = rayHitInfo(rayToGlobal(AARay), worldToRender);
		colors[i] = multipleObjectsTracer::traceRay(info);
		if (iteration < worldToRender->maxAntialiasingIterations && centerColor.distanceSquare(colors[i]) >= worldToRender->minColorDistanceSquare) {
			antiAliase(AARay.origin.x, AARay.origin.y, ++iteration, squareSize / 2);
		}
	}
	
	centerColor.r = (colors[0].r + colors[1].r + colors[2].r + colors[3].r) * 0.25f;
	centerColor.g = (colors[0].g + colors[1].g + colors[2].g + colors[3].g) * 0.25f;
	centerColor.b = (colors[0].b + colors[1].b + colors[2].b + colors[3].b) * 0.25f;

	return centerColor;
}

//aby przekonwertowa� punkt do przestrzeni globalnej potrzebujemy v  pomno�� go przez baz� ortonormaln� 
//a potem doda� lokalizacj� pocz�tku lokalnego uk�au we wsp�rz�dnych globalnych
vector3 orthogonalCamera::pointToGlobal(vector3 point)
{
	point = (u*point.x + v*point.y + w*point.z) + planeCenter;
	return point;
}

//w wypadku wektora dodawanie jest niepotrzebne, bo nie jest on osadzony w konkretnym punkcie przestrzeni
vector3 orthogonalCamera::vectorToGlobal(vector3 vector)
{
	vector = u*vector.x + v*vector.y + w*vector.z;
	vector.normalize();
	return vector;
}

ray orthogonalCamera::rayToGlobal(ray localRay) {
	return ray(pointToGlobal(localRay.origin), vectorToGlobal(localRay.direction));
}

void orthogonalCamera::computeUVW(vector3 &planeCenter, vector3 &lookat, vector3 &up)
{
	//obliczam w, odpowiednik z
	w = lookat - planeCenter;
	w.normalize();
	//obliczam u, odpowiednik x
	u = up.cross(w);
	u.normalize();
	//obliczam v, odpowiednik y
	v = w.cross(u);

	cout << "u: " << u.toString() << endl;
	cout << "v: " << v.toString() << endl;
	cout << "w: " << w.toString() << endl << endl;

	if (planeCenter.x == lookat.x && planeCenter.z == lookat.z && planeCenter.y > lookat.y) { 
		// camera looking vertically down
		u = vector3(0, 0, 1, false);
		v = vector3(1, 0, 0, false);
		w = vector3(0, 1, 0, false);
	}

	if (planeCenter.x == lookat.x && planeCenter.z == lookat.z && planeCenter.y < lookat.y) { 
		// camera looking vertically up
		u = vector3(1, 0, 0, false);
		v = vector3(0, 0, 1, false);
		w = vector3(0, -1, 0, false);
	}
}
