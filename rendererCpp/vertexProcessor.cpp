#include "stdafx.h"
#include "vertexProcessor.h"


vertexProcessor::vertexProcessor():
	obj2world(float4x4::identity()),
	world2view(float4x4::identity()),
	view2proj(float4x4::identity()),
	finalTransformMatrix(float4x4::identity())
{
}

vector3 vertexProcessor::transform(vector3 position)
{
	vector4 result = finalTransformMatrix * vector4(position);
	return vector3(result.x, result.y, result.z) / result.w; //TO OPT operowanie bezpoœrednio na vertexie przekazanym do funkcji
}

vertex vertexProcessor::transform(vertex vertexToTransform)
{
	vertex temp(vertexToTransform);
	temp.position = transform(vertexToTransform.position); //TO OPT operowanie bezpoœrednio na vertexie przekazanym do funkcji
	return temp;
}

vector3 vertexProcessor::illuminate(vertex v, material mat)
{
	return vector3();
}

void vertexProcessor::setPerspective(float fov, float aspect, float nearPlane_z, float farPlane_z)
{
	//float halfFOVInRadians = (fov * 3.14159265358979323846) / 360; //To OPT policzyæ
	//float f = cos(halfFOVInRadians) / sin(halfFOVInRadians);
	//float nearMinusPlane = nearPlane_z - farPlane_z;

	//view2proj = float4x4(
	//	vector4(f / aspect, 0, 0, 0),
	//	vector4(0, f, 0, 0),
	//	vector4(0, 0, (farPlane_z + nearPlane_z) / nearMinusPlane, (2.0F * farPlane_z * nearPlane_z) / nearMinusPlane),
	//	vector4(0, 0, -1.0F, 0));

	float angleInRadians = (fov * 3.14159265358979323846) / 180;
	float f = 1.0F / tan(angleInRadians * 0.5F);
	float nearPlaneMinusFarPlane = nearPlane_z - farPlane_z;

	view2proj = float4x4(
		vector4(f / aspect, 0.0f, 0.0f,                                                         0.0f),
		vector4(0.0f,       f,    0.0f,                                                         0.0f),
		vector4(0.0f,       0.0f, (farPlane_z + nearPlane_z) / (nearPlaneMinusFarPlane),       -1.0f),
		vector4(0.0f,       0.0f, (2.0F * farPlane_z * nearPlane_z) / (nearPlaneMinusFarPlane), 0.0f));
}

void vertexProcessor::setLookAt(vector3 eye, vector3 target, vector3 up)
{
	//if we would like the forward vector (local z axis) to point toward target
	//it should be equal to target - eye
	//however a convention says that cameras look in direction of negative z axis
	//therefore forward vector is flipped
	vector3 forward = (eye - target).normalize(); //reversed so camera looks along negative z
	up.normalize();
	vector3 side = up.cross(forward);
	vector3 up1 = forward.cross(side);

	world2view = float4x4
	(
		vector4(side.x, up1.x, forward.x, 0.0f),
		vector4(side.y, up1.y, forward.y, 0.0f),
		vector4(side.z, up1.z, forward.z, 0.0f),
		vector4(-eye.x , -eye.y, -eye.z, 1.0f)
	);
}

void vertexProcessor::setIdentity()
{
	obj2world.identity();
	world2view.identity();
	view2proj.identity();
}

void vertexProcessor::translate(vector3 v)
{
	obj2world = obj2world * float4x4(
		vector4(1.0f, 0.0f, 0.0f, 0.0f),
		vector4(0.0f, 1.0f, 0.0f, 0.0f),
		vector4(0.0f, 0.0f, 1.0f, 0.0f),
		vector4(v.x,  v.y,  v.z,  1.0f)
	);
}

void vertexProcessor::rotate(vector3 axis, float angle)
{
	float angleInRadians = (angle * 3.14159265358979323846) / 180;//TO OPT obliczyæ sta³¹

	axis.normalize();
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float s = sin(angleInRadians);
	float c = cos(angleInRadians);
	float oneMinusC = 1.0f - c;
	
	obj2world = obj2world * float4x4
	(
		vector4((x * x * oneMinusC) + c,       (x * y * oneMinusC) + z * s,   (x * z * oneMinusC) - y * s,   0.0f),
		vector4((x * y * oneMinusC) - z * s,   (y * y * oneMinusC) + c,       (y * z * oneMinusC) + x * s,   0.0f),
		vector4((x * z * oneMinusC) + y * s,   (y * z * oneMinusC) - x * s,   (z * z * oneMinusC) + c,       0.0f),
		vector4(0.0f,                           0.0f,                         0.0f,                          1.0f)
	);
}

void vertexProcessor::scale(vector3 scale)
{
	obj2world = obj2world * float4x4(
		vector4(scale.x, 0,       0,       0),
		vector4(0,       scale.y, 0,       0),
		vector4(0,       0,       scale.z, 0),
		vector4(0,       0,       0,       1)
	);
}

void vertexProcessor::calculateFinalTransformMatrix()
{
	float4x4 temp = world2view * obj2world;
	finalTransformMatrix = view2proj * temp;
}

void vertexProcessor::setAmbientLight(ambientLight l)
{
	activeAmbientLight = l;
}

void vertexProcessor::addLight(light l)
{
	lightsInTheScene.push_back(l);
}
