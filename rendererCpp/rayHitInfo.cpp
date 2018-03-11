#include "stdafx.h"
#include "rayHitInfo.h"

float rayHitInfo::minIntersectionDistance = 0.00001f;

rayHitInfo::rayHitInfo()
{
	this->t = 0;
	this->hitOccured = false;
	this->normal = vector3();
	this->hitPoint = vector3();
	this->sphericalAnisotropicVector = vector3();
	this->incomingRay = ray();
	this->worldToRender = NULL;
	this->materialToShade = NULL;
	this->reflectionNr = 0;
}

rayHitInfo::rayHitInfo(ray & incomingRay, world *worldToRender)
{
	this->t = 0;
	this->hitOccured = false;
	this->normal = vector3();
	this->hitPoint = vector3();
	this->sphericalAnisotropicVector = vector3();
	this->incomingRay = incomingRay;
	this->worldToRender = worldToRender;
	this->materialToShade = NULL;
	this->reflectionNr = 0;
}

rayHitInfo::rayHitInfo(ray & incomingRay, world * worldToRender, int reflectionNr)
{
	this->t = 0;
	this->hitOccured = false;
	this->normal = vector3();
	this->hitPoint = vector3();
	this->sphericalAnisotropicVector = vector3();
	this->incomingRay = incomingRay;
	this->worldToRender = worldToRender;
	this->materialToShade = NULL;
	this->reflectionNr = reflectionNr;
}

void rayHitInfo::operator=(rayHitInfo & info)
{
	this->t = info.t;
	this->hitOccured = info.hitOccured;
	this->normal = info.normal;
	this->hitPoint = info.hitPoint;
	this->sphericalAnisotropicVector = info.sphericalAnisotropicVector;
	this->incomingRay = info.incomingRay;
	this->worldToRender = info.worldToRender;
	this->materialToShade = info.materialToShade;
	this->reflectionNr = info.reflectionNr;
}

void rayHitInfo::setHit(float &t, vector3 &normal, material *materialToShade, vector3 localHitPoint)
{
	this->t = t;
	this->normal = normal;
	this->hitPoint = localHitPoint;
	this->hitOccured = true;
	this->materialToShade = materialToShade;
	this->sphericalAnisotropicVector = vector3(0, 1, 0, false);
}

void rayHitInfo::setHitAnisotropicSphere(float & t, vector3 & normal, material * materialToShade, vector3 localHitPoint, vector3 anisotropicVector)
{
	this->t = t;
	this->normal = normal;
	this->hitPoint = localHitPoint;
	this->hitOccured = true;
	this->materialToShade = materialToShade;
	this->sphericalAnisotropicVector = anisotropicVector;
}

vector3 rayHitInfo::globalHitPoint()
{
	return incomingRay.origin + incomingRay.direction*t;
}
