#include "stdafx.h"
#include "triangle.h"

bool triangle::hit(rayHitInfo &info)
{
	//sprawdzam czy promie� przecina p�aszczyzn�, na kt�rej le�y tr�jk�t
	if (plane::hit(info))
	{
		//plane ustawi�a, �e by�o z ni� przeci�cie, ale to nie znaczy, �e przeci�li�my tr�jk�t
		info.hitOccured = false;

		//obliczam wektory mi�dzy punktem przeci�cia i wierzcho�kami tr�jk�ta
		vector3 DA = A.position - info.hitPoint;
		vector3 DB = B.position - info.hitPoint;
		vector3 DC = C.position - info.hitPoint;

		//sprawdzam ze zwyk�� normalk�
		//cross = u*v*sin(k�t)
		//je�li k�t < 180 stopni wychodzi wektor r�wnoleg�y do normalnego
		//je�li k�t > 180 wychodzi wektor przeciwny, bo sin < 0
		//dot = |u|*|v|*cos(k�t)
		//je�li r�wnoleg�e wychodzi cos = 1 > 0
		//je�li k�t 180, to wychodzi cos = -1 < 0
		//je�li wszystkie dot dodatnie,to znaczy, �e k�ty mi�dzy wektorami
		//DA, DB, DC s� mniejsze od 180, czyli D jest w �rodku tr�jk�ta
		if ((DA.cross(DB)).dot(normal) >= info.minIntersectionDistance &&
			(DB.cross(DC)).dot(normal) >= info.minIntersectionDistance &&
			(DC.cross(DA)).dot(normal) >= info.minIntersectionDistance)
			info.hitOccured = true;

		//i z odwr�con� normalk�
		if ((DA.cross(DB)).dot(-normal) >= info.minIntersectionDistance &&
			(DB.cross(DC)).dot(-normal) >= info.minIntersectionDistance &&
			(DC.cross(DA)).dot(-normal) >= info.minIntersectionDistance)
			info.hitOccured = true;
	}
	return false;
}
