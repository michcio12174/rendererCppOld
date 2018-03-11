#include "stdafx.h"
#include "sphere.h"

sphere::sphere()
{
}

sphere::sphere(vector3 origin, float radius, material *materialToUse)
{
	this->origin = origin;
	this->radius = radius;
	this->materialToUse = materialToUse;
}

sphere::sphere(const sphere & sphere)
{
	this->origin = sphere.origin;
	this->radius = sphere.radius;
	this->materialToUse = sphere.materialToUse;
}


sphere::~sphere()
{
}


bool sphere::hit(rayHitInfo &info)
{
	vector3 rayOriginMinusSphereOrigin = info.incomingRay.origin - origin;
	float b = rayOriginMinusSphereOrigin.dot(info.incomingRay.direction); //b w r�wnaniu ax^2 + bx + c = 0
	float delta = b*b - rayOriginMinusSphereOrigin.dot(rayOriginMinusSphereOrigin) + radius*radius;

	if (delta >= 0.0001) {
		if (delta < 0.0001 && delta > -0.0001){ //w praktyce je�li delta=0 - jedno przeci�cie
			float t = -b;
			vector3 intersection = info.incomingRay.origin + info.incomingRay.direction*t;
			vector3 tempNormal = intersection - origin;

			//przekszta�cam globalny punkt na lokalny z pocz�tkiem uk�adu w �rodku sfery
			intersection = intersection - origin; 

			info.setHit(t, tempNormal, materialToUse, intersection);
			return true;
		}
		else { //dwa przeci�cia, delta>0
			delta = sqrt(delta);
			float t1 = -b - delta;  //delta to pierwiastek, wiec zawsze dodatnia
			float t2 = -b + delta;  //st�d zawsze t1<t2

			if (t2 < info.minIntersectionDistance) {//je�eli t = 0 to i tak nie uznajemy przeci�cia
				return false;
			}
			else if (t1 < info.minIntersectionDistance) {
				vector3 intersection2 = info.incomingRay.origin + info.incomingRay.direction*t2;
				vector3 tempNormal = intersection2 - origin;
				tempNormal.normalize();

				//przekszta�cam globalny punkt na lokalny z pocz�tkiem uk�adu w �rodku sfery
				intersection2 = intersection2 - origin;

				info.setHit(t2, tempNormal, materialToUse, intersection2);
				return true;
			}
			else {
				vector3 intersection1 = info.incomingRay.origin + info.incomingRay.direction*t1;
				vector3 tempNormal = intersection1 - origin;
				tempNormal.normalize();

				//przekszta�cam globalny punkt na lokalny z pocz�tkiem uk�adu w �rodku sfery
				intersection1 = intersection1 - origin;

				info.setHit(t1, tempNormal, materialToUse, intersection1);
				return true;
			}
		}
		
	}
	return false;
}

vector3 sphere::getNormal(vector3 point)
{
	vector3 temp = point - origin;
	temp.normalize();
	return temp;
}
