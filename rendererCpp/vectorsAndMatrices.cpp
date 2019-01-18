#include "stdafx.h"
#include "vectorsAndMatrices.h"
#include <iomanip>

const static float epsilon = 0.000001; //u�ywany do sprawdzenia, czy normalizowany wektor nie jest za ma�y

//------------------------------------------------------------vector3------------------------------------------------------------

vector3::vector3() :
	x(0),
	y(0),
	z(0)
{
}

vector3::vector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}

vector3::vector3(float x, float y, float z, bool normalize) :
	x(x),
	y(y),
	z(z)
{
	if (normalize) this->normalize();
}

vector3::vector3(const vector3 & vector) :
	x(vector.x),
	y(vector.y),
	z(vector.z)
{
}

string vector3::toString()
{
	string a = "vector3(" + to_string(this->x) + ", " + to_string(this->y) + ", " + to_string(this->z) + ")";
	return a;
}

vector3 vector3::operator-() const
{
	return vector3(-this->x, -this->y, -this->z, false);
}

vector3 vector3::operator*(float const &k) const
{
	return vector3(this->x*k, this->y*k, this->z*k, false);
}

vector3 vector3::operator/(float const &k) const
{
	return vector3(this->x / k, this->y / k, this->z / k, false);
}

vector3 vector3::operator+(vector3 const &b) const
{
	return vector3(this->x + b.x, this->y + b.y, this->z + b.z, false);
}

vector3 vector3::operator-(vector3 const &b) const
{
	return vector3(this->x - b.x, this->y - b.y, this->z - b.z, false);
}

vector3 vector3::operator*(vector3 const &b) const
{
	return vector3(this->x * b.x, this->y * b.y, this->z * b.z, false);
}

vector3 vector3::operator*=(float4x4 & matrix)
{
	vector4 temp(*this);

	this->x = (matrix[0][0] * temp.x) + (matrix[0][1] * temp.y) + (matrix[0][2] * temp.z) + (matrix[0][3] * temp.w);
	this->y = (matrix[1][0] * temp.x) + (matrix[1][1] * temp.y) + (matrix[1][2] * temp.z) + (matrix[1][3] * temp.w);
	this->z = (matrix[2][0] * temp.x) + (matrix[2][1] * temp.y) + (matrix[2][2] * temp.z) + (matrix[2][3] * temp.w);

	return *this;
}

vector3 vector3::operator/(vector3 const &b) const
{
	return vector3(this->x / b.x, this->y / b.y, this->z / b.z, false);
}

float & vector3::operator[](int i)
{
	if (i == 0) return x;
	else if (i == 1) return y;
	else if (i == 2) return z;
	else return z;
}

void vector3::operator=(vector3 const & b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
}

float vector3::length() const
{
	return sqrt(x*x + y * y + z * z);
}

float vector3::lengthSquare() const
{
	return pow(this->length(), 2);
}

float vector3::dot(vector3 const &b) const
{
	return this->x * b.x + this->y * b.y + this->z * b.z;
}

vector3 vector3::cross(vector3 const &b) const
{
	return vector3(
		this->y*b.z - this->z*b.y,
		this->z*b.x - this->x*b.z,
		this->x*b.y - this->y*b.x,
		true);
}

void vector3::scaleToOne()
{
	float maximum = max(r, max(g, b));
	if (maximum > 1) {
		r = r / maximum;
		g = g / maximum;
		b = b / maximum;
	}
	if (r < 0)r = 0;
	if (g < 0)g = 0;
	if (b < 0)b = 0;
}

void vector3::saturate()
{
	r = max(0.0f, min(1.0f, r));
	g = max(0.0f, min(1.0f, g));
	b = max(0.0f, min(1.0f, b));
}

void vector3::toEightBit()
{
	scaleToOne();
	r = r * 255;
	g = g * 255;
	b = b * 255;
}

int vector3::toInt()
{
	toEightBit();
	int result = 0;
	result |= ((unsigned char)255 << 24); //alfa
	result |= ((unsigned char)this->r << 16);
	result |= ((unsigned char)this->g << 8);
	result |= ((unsigned char)this->b);
	return result;
}

float vector3::distanceSquare(vector3 secondVector)
{
	return ((secondVector.r - r)*(secondVector.r - r) +
		(secondVector.g - g)*(secondVector.g - g) +
		(secondVector.b - b)*(secondVector.b - b));
}

vector3 vector3::normalize()
{
	float length = this->length();
	if (length > epsilon) {
		float inversedLength = 1 / length;
		this->x = this->x*inversedLength;
		this->y = this->y*inversedLength;
		this->z = this->z*inversedLength;
	}

	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	return *this;
}

vector3 vector3::reflect(vector3 normal)
{
	return *this - normal * (normal.dot(*this) * 2);
}

//------------------------------------------------------------vector4------------------------------------------------------------

vector4::vector4() :
	x(0),
	y(0),
	z(0),
	w(1)
{
}

vector4::vector4(float x, float y, float z) :
	x(x),
	y(y),
	z(z),
	w(1)
{
}

vector4::vector4(float x, float y, float z, float w) :
	x(x),
	y(y),
	z(z),
	w(w)
{
}

vector4::vector4(float x, float y, float z, float w, bool normalize) :
	x(x),
	y(y),
	z(z),
	w(w)
{
	if (normalize) this->normalize();
}

vector4::vector4(const vector4 & vector) :
	x(vector.x),
	y(vector.y),
	z(vector.z),
	w(vector.w)
{
}

vector4::vector4(const vector3 & vector) :
	x(vector.x),
	y(vector.y),
	z(vector.z),
	w(1)
{
}

vector4::vector4(unsigned int argb)
{
	this->a = argb >> 24 & 255;
	this->r = argb >> 16 & 255;
	this->g = argb >> 8 & 255;
	this->b = argb & 255;
	scaleToOne();
}

string vector4::toString()
{
	string a = "vector4(" + to_string(this->x) + ", "
		+ to_string(this->y) + ", "
		+ to_string(this->z) + ", "
		+ to_string(this->w) + ")";
	return a;
}

vector4 vector4::operator-() const
{
	return vector4(-this->x, -this->y, -this->z, -this->w, false);
}

vector4 vector4::operator*(float const &k) const
{
	return vector4(this->x*k, this->y*k, this->z*k, this->w*k, false);
}

vector4 vector4::operator/(float const &k) const
{
	return vector4(this->x / k, this->y / k, this->z / k, this->w / k, false);
}

vector4 vector4::operator+(vector4 const &b) const
{
	return vector4(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w, false);
}

vector4 vector4::operator-(vector4 const &b) const
{
	return vector4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w, false);
}

vector4 vector4::operator*(vector4 const &b) const
{
	return vector4(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w, false);
}

vector4 vector4::operator*=(float4x4 & matrix)
{
	vector4 temp(*this);

	this->x = (matrix[0][0] * temp.x) + (matrix[0][1] * temp.y) + (matrix[0][2] * temp.z) + (matrix[0][3] * temp.w);
	this->y = (matrix[1][0] * temp.x) + (matrix[1][1] * temp.y) + (matrix[1][2] * temp.z) + (matrix[1][3] * temp.w);
	this->z = (matrix[2][0] * temp.x) + (matrix[2][1] * temp.y) + (matrix[2][2] * temp.z) + (matrix[2][3] * temp.w);
	this->w = (matrix[3][0] * temp.x) + (matrix[3][1] * temp.y) + (matrix[3][2] * temp.z) + (matrix[3][3] * temp.w);

	return *this;
}

vector4 vector4::operator/(vector4 const &b) const
{
	return vector4(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w, false);
}

float& vector4::operator[](int i)
{
	if (i == 0) return x;
	else if (i == 1) return y;
	else if (i == 2) return z;
	else if (i == 3) return w;
	else return w;
}

void vector4::operator=(vector4 const & b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
	this->w = b.w;
}

void vector4::operator=(unsigned int const & argb)
{
	this->a = argb >> 24 & 255;
	this->r = argb >> 16 & 255;
	this->g = argb >> 8 & 255;
	this->b = argb & 255;
	scaleToOne();
}

float vector4::length() const
{
	return sqrt(x*x + y * y + z * z + w * w);
}

float vector4::lengthSquare() const
{
	return pow(this->length(), 2);
}

float vector4::dot(vector4 const &b) const
{
	return this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w;
}

vector4 vector4::cross(vector4 const b) const
{
	return vector4(
		this->y*b.z - this->z*b.y,
		this->z*b.x - this->x*b.z,
		this->x*b.y - this->y*b.x,
		1);
}

void vector4::scaleToOne()
{
	float maximum = max(r, max(g, b));
	if (maximum > 1) {
		r = r / maximum;
		g = g / maximum;
		b = b / maximum;
	}
	if (r < 0)r = 0;
	if (g < 0)g = 0;
	if (b < 0)b = 0;

	a = max(0.0f, min(1.0f, a)); //alfy nie skaluj� z reszt� koloru - je�li jest wi�ksza od 1 ustawiam na 1
}

void vector4::saturate()
{
	r = max(0.0f, min(1.0f, r));
	g = max(0.0f, min(1.0f, g));
	b = max(0.0f, min(1.0f, b));
	a = max(0.0f, min(1.0f, a));
}

void vector4::toEightBit()
{
	scaleToOne();
	r = r * 255;
	g = g * 255;
	b = b * 255;
	a = a * 255;
}

int vector4::toInt()
{
	toEightBit();
	int result = 0;
	result |= ((unsigned char)this->a << 24); //alfa
	result |= ((unsigned char)this->r << 16);
	result |= ((unsigned char)this->g << 8);
	result |= ((unsigned char)this->b);
	return result;
}

vector4 vector4::normalize()
{
	float length = this->length();
	if (length > epsilon) {
		float inversedLength = 1 / length;
		this->x = this->x*inversedLength;
		this->y = this->y*inversedLength;
		this->z = this->z*inversedLength;
		this->w = this->w*inversedLength;
	}

	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	return *this;
}

//------------------------------------------------------------float4x4------------------------------------------------------------

float4x4::float4x4()
{
	row1 = vector4(0, 0, 0, 0);
	row2 = vector4(0, 0, 0, 0);
	row3 = vector4(0, 0, 0, 0);
	row4 = vector4(0, 0, 0, 0);
}

float4x4::float4x4(const vector4 &row1, const vector4 &row2, const vector4 &row3, const vector4 &row4):
	row1(row1),
	row2(row2),
	row3(row3),
	row4(row4)
{}

void float4x4::operator=(float4x4 const &B)
{
	row1 = B.row1;
	row2 = B.row2;
	row3 = B.row3;
	row4 = B.row4;
}

//in reality performs multiplication of vector by matrix, not matrix by vector
vector4 float4x4::operator*(vector3 &vector)
{
	vector4 C;
	for (int i = 0; i < 4; i++) {
		C[i] = vector[0] * (*this)[0][i] +
			vector[1] * (*this)[1][i] +
			vector[2] * (*this)[2][i] +
			(*this)[3][i];
	}
	return C;
}

//in reality performs multiplication of vector by matrix, not matrix by vector
vector4 float4x4::operator*(vector4 &vector)
{
	vector4 C;
	for (int i = 0; i < 4; i++) {
		C[i] = vector[0] * (*this)[0][i] +
			vector[1] * (*this)[1][i] +
			vector[2] * (*this)[2][i] +
			vector[3] * (*this)[3][i];
	}
	return C;
}

float4x4 float4x4::operator*(float4x4 B)
{
	float4x4 C;
	int i, j; //i - kolumna, j - rz�d
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			C[i][j] = (*this)[i][0] * B[0][j] +
				(*this)[i][1] * B[1][j] +
				(*this)[i][2] * B[2][j] +
				(*this)[i][3] * B[3][j];
		}
	}
	return C;
}

vector4& float4x4::operator[](int i)
{
	if (i == 0) return row1;
	else if (i == 1) return row2;
	else if (i == 2) return row3;
	else if (i == 3) return row4;
	else {
		return row4;
		cout << "a row of number higher that 4 was requested from 4x4 matrix, fourth row returned" << endl;
	}
}

float4x4 float4x4::transpose()
{
	float4x4 temp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[j][i] = (*this)[i][j];
		}
	}
	*this = temp;

	return *this;
}

string float4x4::toString()
{
	string matrix;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			matrix += to_string((int)(*this)[i][j]) + " "; //liczby ca�kowite zajmuj� mniej miejsca - �atwiej czyta� output
			//matrix += to_string((*this)[i][j]) + " ";
		}
		matrix += "\n";
	}
	return matrix;
}

float4x4 float4x4::identity()
{
	float4x4 s(vector4(1, 0, 0, 0),
		vector4(0, 1, 0, 0),
		vector4(0, 0, 1, 0),
		vector4(0, 0, 0, 1));
	return s;
}

float4x4 float4x4::inverse()//todo
{
	float4x4 inv;

	inv[0][0] = (*this)[1][1] * (*this)[2][2] * (*this)[3][3] - (*this)[1][1] * (*this)[2][3] * (*this)[3][2] - (*this)[2][1] * (*this)[1][2] * (*this)[3][3] +
		(*this)[2][1] * (*this)[1][3] * (*this)[3][2] + (*this)[3][1] * (*this)[1][2] * (*this)[2][3] - (*this)[3][1] * (*this)[1][3] * (*this)[2][2];

	inv[1][0] = -(*this)[1][0] * (*this)[2][2] * (*this)[3][3] + (*this)[1][0] * (*this)[2][3] * (*this)[3][2] + (*this)[2][0] * (*this)[1][2] * (*this)[3][3] -
		(*this)[2][0] * (*this)[1][3] * (*this)[3][2] - (*this)[3][0] * (*this)[1][2] * (*this)[2][3] + (*this)[3][0] * (*this)[1][3] * (*this)[2][2];

	inv[2][0] = (*this)[1][0] * (*this)[2][1] * (*this)[3][3] - (*this)[1][0] * (*this)[2][3] * (*this)[3][1] - (*this)[2][0] * (*this)[1][1] * (*this)[3][3] +
		(*this)[2][0] * (*this)[1][3] * (*this)[3][1] + (*this)[3][0] * (*this)[1][1] * (*this)[2][3] - (*this)[3][0] * (*this)[1][3] * (*this)[2][1];

	inv[3][0] = -(*this)[1][0] * (*this)[2][1] * (*this)[3][2] + (*this)[1][0] * (*this)[2][2] * (*this)[3][1] + (*this)[2][0] * (*this)[1][1] * (*this)[3][2] -
		(*this)[2][0] * (*this)[1][2] * (*this)[3][1] - (*this)[3][0] * (*this)[1][1] * (*this)[2][2] + (*this)[3][0] * (*this)[1][2] * (*this)[2][1];

	inv[0][1] = -(*this)[0][1] * (*this)[2][2] * (*this)[3][3] + (*this)[0][1] * (*this)[2][3] * (*this)[3][2] + (*this)[2][1] * (*this)[0][2] * (*this)[3][3] -
		(*this)[2][1] * (*this)[0][3] * (*this)[3][2] - (*this)[3][1] * (*this)[0][2] * (*this)[2][3] + (*this)[3][1] * (*this)[0][3] * (*this)[2][2];

	inv[1][1] = (*this)[0][0] * (*this)[2][2] * (*this)[3][3] - (*this)[0][0] * (*this)[2][3] * (*this)[3][2] - (*this)[2][0] * (*this)[0][2] * (*this)[3][3] +
		(*this)[2][0] * (*this)[0][3] * (*this)[3][2] + (*this)[3][0] * (*this)[0][2] * (*this)[2][3] - (*this)[3][0] * (*this)[0][3] * (*this)[2][2];

	inv[2][1] = -(*this)[0][0] * (*this)[2][1] * (*this)[3][3] + (*this)[0][0] * (*this)[2][3] * (*this)[3][1] + (*this)[2][0] * (*this)[0][1] * (*this)[3][3] -
		(*this)[2][0] * (*this)[0][3] * (*this)[3][1] - (*this)[3][0] * (*this)[0][1] * (*this)[2][3] + (*this)[3][0] * (*this)[0][3] * (*this)[2][1];

	inv[3][1] = (*this)[0][0] * (*this)[2][1] * (*this)[3][2] - (*this)[0][0] * (*this)[2][2] * (*this)[3][1] - (*this)[2][0] * (*this)[0][1] * (*this)[3][2] +
		(*this)[2][0] * (*this)[0][2] * (*this)[3][1] + (*this)[3][0] * (*this)[0][1] * (*this)[2][2] - (*this)[3][0] * (*this)[0][2] * (*this)[2][1];

	inv[0][2] = (*this)[0][1] * (*this)[1][2] * (*this)[3][3] - (*this)[0][1] * (*this)[1][3] * (*this)[3][2] - (*this)[1][1] * (*this)[0][2] * (*this)[3][3] +
		(*this)[1][1] * (*this)[0][3] * (*this)[3][2] + (*this)[3][1] * (*this)[0][2] * (*this)[1][3] - (*this)[3][1] * (*this)[0][3] * (*this)[1][2];

	inv[1][2] = -(*this)[0][0] * (*this)[1][2] * (*this)[3][3] + (*this)[0][0] * (*this)[1][3] * (*this)[3][2] + (*this)[1][0] * (*this)[0][2] * (*this)[3][3] -
		(*this)[1][0] * (*this)[0][3] * (*this)[3][2] - (*this)[3][0] * (*this)[0][2] * (*this)[1][3] + (*this)[3][0] * (*this)[0][3] * (*this)[1][2];

	inv[2][2] = (*this)[0][0] * (*this)[1][1] * (*this)[3][3] - (*this)[0][0] * (*this)[1][3] * (*this)[3][1] - (*this)[1][0] * (*this)[0][1] * (*this)[3][3] +
		(*this)[1][0] * (*this)[0][3] * (*this)[3][1] + (*this)[3][0] * (*this)[0][1] * (*this)[1][3] - (*this)[3][0] * (*this)[0][3] * (*this)[1][1];

	inv[3][2] = -(*this)[0][0] * (*this)[1][1] * (*this)[3][2] + (*this)[0][0] * (*this)[1][2] * (*this)[3][1] + (*this)[1][0] * (*this)[0][1] * (*this)[3][2] -
		(*this)[1][0] * (*this)[0][2] * (*this)[3][1] - (*this)[3][0] * (*this)[0][1] * (*this)[1][2] + (*this)[3][0] * (*this)[0][2] * (*this)[1][1];

	inv[0][3] = -(*this)[0][1] * (*this)[1][2] * (*this)[2][3] + (*this)[0][1] * (*this)[1][3] * (*this)[2][2] + (*this)[1][1] * (*this)[0][2] * (*this)[2][3] -
		(*this)[1][1] * (*this)[0][3] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2] * (*this)[1][3] + (*this)[2][1] * (*this)[0][3] * (*this)[1][2];

	inv[1][3] = (*this)[0][0] * (*this)[1][2] * (*this)[2][3] - (*this)[0][0] * (*this)[1][3] * (*this)[2][2] - (*this)[1][0] * (*this)[0][2] * (*this)[2][3] +
		(*this)[1][0] * (*this)[0][3] * (*this)[2][2] + (*this)[2][0] * (*this)[0][2] * (*this)[1][3] - (*this)[2][0] * (*this)[0][3] * (*this)[1][2];

	inv[2][3] = -(*this)[0][0] * (*this)[1][1] * (*this)[2][3] + (*this)[0][0] * (*this)[1][3] * (*this)[2][1] + (*this)[1][0] * (*this)[0][1] * (*this)[2][3] -
		(*this)[1][0] * (*this)[0][3] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1] * (*this)[1][3] + (*this)[2][0] * (*this)[0][3] * (*this)[1][1];

	inv[3][3] = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] - (*this)[0][0] * (*this)[1][2] * (*this)[2][1] - (*this)[1][0] * (*this)[0][1] * (*this)[2][2] +
		(*this)[1][0] * (*this)[0][2] * (*this)[2][1] + (*this)[2][0] * (*this)[0][1] * (*this)[1][2] - (*this)[2][0] * (*this)[0][2] * (*this)[1][1];

	float det = (*this)[0][0] * inv[0][0] + (*this)[0][1] * inv[1][0] + (*this)[0][2] * inv[2][0] + (*this)[0][3] * inv[3][0];

	if (det == 0)
		return *this;

	det = 1.0 / det;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			inv[x][y] *= det;
		}
	}

	return inv;
}

