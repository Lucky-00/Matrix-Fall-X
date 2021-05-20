//-----------------------------------------------------------------------------
//           Name: vector3f.h
//         Author: Kevin Harris
//  Last Modified: 09/09/02
//    Description: Header file for OpenGL compatible utility class for a 3
//                 component vector of doubles.
//
//  NOTE: This class has been left unoptimized for readability.
//-----------------------------------------------------------------------------

#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_

#include <cmath>

class vector3f
{
public:

	double x;
	double y;
	double z;

	vector3f(void);
	~vector3f(void);

	vector3f(double x_, double y_, double z_);
	void set(double x_, double y_, double z_);
	double length(void);
	void normalize(void);

	// Operators...
	vector3f operator + (const vector3f& other);
	vector3f operator - (const vector3f& other);
	vector3f operator * (const vector3f& other);
	vector3f operator / (const vector3f& other);

	vector3f operator * (const double scalar);
	friend vector3f operator * (const double scalar, const vector3f& other);

	vector3f& operator = (const vector3f& other);
	vector3f& operator += (const vector3f& other);
	vector3f& operator -= (const vector3f& other);

	vector3f operator + (void) const;
	vector3f operator - (void) const;

	// Static utility methods
	static double distance(const vector3f& v1, const vector3f& v2);
	static double dotProduct(const vector3f& v1, const vector3f& v2);
	static vector3f crossProduct(const vector3f& v1, const vector3f& v2);
};

#endif /* _VECTOR3F_H_ */
