#pragma once

using namespace std;

struct vector4;
struct float4x4;

//represents vector and rgb color
struct vector3
{
	vector3();
	vector3(float x, float y, float z);
	vector3(float x, float y, float z, bool normalize);
	vector3(const vector3 &vector);

	string toString();

	vector3 operator - () const;
	vector3 operator * (float const &k) const;
	vector3 operator / (float const &k) const;
	vector3 operator + (vector3 const &b) const;
	vector3 operator - (vector3 const &b) const;
	vector3 operator * (vector3 const &b) const;
	vector3 operator *= (float4x4 & matrix);
	vector3 operator / (vector3 const &b) const;
	float & operator [] (int i);
	void operator = (vector3 const &b);

	//vector funcions
	vector3 normalize();
	float length() const;
	float lengthSquare() const;
	float dot(vector3 const &b) const;
	vector3 reflect(vector3 normal);
	vector3 cross(vector3 const &b) const;

	//color functions
	void scaleToOne(); //scales whole colour to value between 0 and 1
	void saturate(); //cuts value to between 0 and 1
	void toEightBit();
	int toInt();
	float distanceSquare(vector3 secondVector);

	union {
		float x;
		float r;
	};
	union {
		float y;
		float g;
	};
	union {
		float z;
		float b;
	};
};

//represents vector and rgba color
struct vector4
{
	vector4();
	vector4(float x, float y, float z);
	vector4(float x, float y, float z, float w);
	vector4(float x, float y, float z, float w, bool normalize);
	vector4(const vector4 &vector);
	vector4(const vector3 &vector);
	vector4(unsigned int argb);

	string toString();

	vector4 operator - () const;
	vector4 operator * (float const &k) const;
	vector4 operator / (float const &k) const;
	vector4 operator + (vector4 const &b) const;
	vector4 operator - (vector4 const &b) const;
	vector4 operator * (vector4 const &b) const;
	vector4 operator *= (float4x4 & matrix);
	vector4 operator / (vector4 const &b) const;
	float& operator [] (int i);
	void operator = (vector4 const &b);
	void operator = (unsigned int const &argb);

	//vector functions
	vector4 normalize();
	float length() const;
	float lengthSquare() const;
	float dot(vector4 const &b) const;
	vector4 cross(vector4 const b) const;

	//color functions
	void scaleToOne(); //scales whole colour to value between 0 and 1
	void saturate(); //cuts value to between 0 and 1
	void toEightBit();
	int toInt();

	union {
		float x;
		float r;
	};
	union {
		float y;
		float g;
	};
	union {
		float z;
		float b;
	};
	union {
		float w;
		float a;
	};
};

//implemented in row-major order
struct float4x4
{
	float4x4();
	//each vector represents one row of the matrix
	float4x4(const vector4 &row1, const vector4 &row2, const vector4 &row3, const vector4 &row4);

	void operator = (float4x4 const &B);
	vector4 operator * (vector3 &vector);
	vector4 operator * (vector4 &vector);
	float4x4 operator * (float4x4 B);
	vector4& operator [] (int i);

	string toString();
	float4x4 transpose();
	static float4x4 identity();
	float4x4 inverse();

	vector4 row1, row2, row3, row4;
};

