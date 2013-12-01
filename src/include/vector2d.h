#ifndef UGINE_VECTOR2D_H
#define UGINE_VECTOR2D_H

#include "types.h"
#include "math.h"
#include <math.h>

class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D();
	Vector2D( const float x, const float y );

	float Magnitude() const;
	float sqrtMagnitude() const;
	Vector2D Normalize() const;
	void GetNormalized();
	float GetScalar() const;
	// Operators
	Vector2D operator==( const Vector2D &other ) const;
	Vector2D operator=( const Vector2D &other ) const;
	Vector2D operator+=( const Vector2D &other ) const;
	Vector2D operator-=( const Vector2D &other ) const;
	Vector2D operator+( const Vector2D &other ) const;
	Vector2D operator-( const Vector2D &other ) const;
	Vector2D operator*( const Vector2D &other ) const;
	// Statics
	static Vector2D Up();
	static Vector2D Down();
	static Vector2D Right();
	static Vector2D Left();
	static Vector2D FromPolar( const float a, const float r );
	static float Distance( const Vector2D v01, const Vector2D v02 );
	static float Angle( const Vector2D v01, const Vector2D v02 );
};

// Operator non-member para poder usar un param de tipo distinto al objeto
Vector2D operator*( const float scale, const Vector2D vector );

#endif