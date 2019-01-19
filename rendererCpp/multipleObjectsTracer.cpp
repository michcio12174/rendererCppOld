#include "stdafx.h"
#include "multipleObjectsTracer.h"
#include "material.h"

vector3 multipleObjectsTracer::traceRay(rayHitInfo info)
{
	//info to informacja o najbli�szym przeci�ciu, temp to informacja o przeci�ziu w aktualej iteracji p�tli
	rayHitInfo temp = info; 
	if (info.worldToRender) {
		for (geometricObject *currentObject : info.worldToRender->objectsInTheScene) {
			currentObject->hit(temp);
			//zmieniamy info na temp je�li nie by�o jeszcze trafienia lub trafienie by�o dalej od kamery
			if (temp.hitOccured && (!info.hitOccured || temp.t < info.t)) {
				info = temp;
			}
		}
	}
	else cout << "null world pointer" << endl;

	if (info.materialToShade == NULL) return vector3(0, 0, 0);
	else return info.materialToShade->shade(info);
}

void multipleObjectsTracer::traceShadowRay(rayHitInfo &info, light *lightToUse)
{
	int size = info.worldToRender->objectsInTheScene.size();
	
	//funkcje hit ustawiaj� info o przeci�ciu tylko je�li jest trafienie
	rayHitInfo temp = info;
	if (info.worldToRender) {
		//cout << "tracing shadowwww" << endl;
		//if a light is a point light, we check if there was a hit between light origin and shaded point
		if (lightToUse->isPointLight) {
			float distanceToLightSource = (lightToUse->origin - info.incomingRay.origin).x / info.incomingRay.direction.x;
			//wychodzimy z p�tli od tazu kiedy by�o przeci�cie, nie trzeba sprawdza� innych obiekt�w
			for (int i = 0; i < size; i++) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				//we change info only if hit in temp is between light source and shadow ray origin
				if (temp.hitOccured && temp.t < distanceToLightSource) {
					info = temp; 
					return;
				}
			}
		}
		//if a light is a directional light we check if there is any hit starting from shaded point in inverse direction of light
		else {
			//wychodzimy z p�tli od tazu kiedy by�o przeci�cie, nie trzeba sprawdza� innych obiekt�w
			for (int i = 0; i < size; i++) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				if (temp.hitOccured) { 
					info = temp; 
					return;
				}
			}
		}
	}
	else cout << "null world pointer" << endl;
}
