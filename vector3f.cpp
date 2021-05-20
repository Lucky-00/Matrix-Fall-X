//-----------------------------------------------------------------------------
//           Name: vector3f.cpp
//         Author: Kevin Harris
//  Last Modified: 09/09/02
//    Description: Source file for OpenGL compatible utility class for a 3
//                 component vector of doubles.
//
//  NOTE: This class has been left unoptimized for readability.
//-----------------------------------------------------------------------------

#include "vector3f.h"

vector3f::vector3f(void)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vector3f::vector3f(double x_, double y_, double z_)
{
	x = x_;
	y = y_;
	z = z_;
}

vector3f::~vector3f(void)
{
}

void vector3f::set(double x_, double y_, double z_)
{
	x = x_;
	y = y_;
	z = z_;
}

double vector3f::length(void)
{
	return((double)sqrt(x * x + y * y + z * z));
}

void vector3f::normalize(void)
{
	double fLength = length();

	x = x / fLength;
	y = y / fLength;
	z = z / fLength;
}

//
// Operators...
//

vector3f vector3f::operator + (const vector3f& other)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = x + other.x;
	vResult.y = y + other.y;
	vResult.z = z + other.z;

	return vResult;
}

vector3f vector3f::operator + (void) const
{
	return *this;
}

vector3f vector3f::operator - (const vector3f& other)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = x - other.x;
	vResult.y = y - other.y;
	vResult.z = z - other.z;

	return vResult;
}

vector3f vector3f::operator - (void) const
{
	vector3f vResult(-x, -y, -z);

	return vResult;
}

vector3f vector3f::operator * (const vector3f& other)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = x * other.x;
	vResult.y = y * other.y;
	vResult.z = z * other.z;

	return vResult;
}

vector3f vector3f::operator * (const double scalar)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = x * scalar;
	vResult.y = y * scalar;
	vResult.z = z * scalar;

	return vResult;
}

vector3f operator * (const double scalar, const vector3f& other)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = other.x * scalar;
	vResult.y = other.y * scalar;
	vResult.z = other.z * scalar;

	return vResult;
}

vector3f vector3f::operator / (const vector3f& other)
{
	vector3f vResult(0.0f, 0.0f, 0.0f);

	vResult.x = x / other.x;
	vResult.y = y / other.y;
	vResult.z = z / other.z;

	return vResult;
}

vector3f& vector3f::operator = (const vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

vector3f& vector3f::operator += (const vector3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

vector3f& vector3f::operator -= (const vector3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

//
// Static utility methods...
//

double vector3f::distance(const vector3f& v1, const vector3f& v2)
{
	double dx = v1.x - v2.x;
	double dy = v1.y - v2.y;
	double dz = v1.z - v2.z;

	return (double)sqrt(dx * dx + dy * dy + dz * dz);
}

double vector3f::dotProduct(const vector3f& v1, const vector3f& v2)
{
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

vector3f vector3f::crossProduct(const vector3f& v1, const vector3f& v2)
{
	vector3f vCrossProduct;

	vCrossProduct.x = v1.y * v2.z - v1.z * v2.y;
	vCrossProduct.y = -v1.x * v2.z + v1.z * v2.x;
	vCrossProduct.z = v1.x * v2.y - v1.y * v2.x;

	return vCrossProduct;
}