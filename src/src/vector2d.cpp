#include "../include/vector2d.h"

// ----------------------------------- //
Vector2D::Vector2D() : x( 0 ), y( 0 ) {}

// ----------------------------------- //
Vector2D::Vector2D( const float _x, const float _y ) : x( _x ), y( _y ) {}

// ----------------------------------- //
Vector2D Vector2D::FromPolar( const float a, const float r )
{
	return Vector2D( r * cos( a ), r * sin( a ) );
}

// ----------------------------------- //
float Vector2D::Angle( const Vector2D v01, const Vector2D v02 )
{
	return abs( atan2( v01.y, v01.x ) - atan2( v02.y, v02.x ) );
}

// ----------------------------------- //
float Vector2D::Distance( const Vector2D v01, const Vector2D v02 )
{
	return ( ( v01 - v02 ).Magnitude() );
}

// ----------------------------------- //
float Vector2D::Magnitude() const
{
	return sqrt( x * x + y * y );
}

// ----------------------------------- //
float Vector2D::sqrtMagnitude() const
{
	return x * x + y * y;
}

// ----------------------------------- //
Vector2D Vector2D::Normalize() const
{
	float mag = Magnitude();
	
	if ( mag > 0 )
	{
		return Vector2D( x / mag, y / mag );
	}
	else
	{
		return Vector2D( 0, 0 );
	}
}

// ----------------------------------- //
void Vector2D::GetNormalized()
{
	float mag = Magnitude();

	if ( mag > 0 )
	{
		x /= mag;
		y /= mag;
	}
	else
	{
		x = 0;
		y = 0;
	}
}

// ----------------------------------- //
Vector2D Vector2D::Up()
{
	return Vector2D( 0, 1 );
}

// ----------------------------------- //
Vector2D Vector2D::Down()
{
	return Vector2D( 0, -1 );
}

// ----------------------------------- //
Vector2D Vector2D::Right()
{
	return Vector2D( 1, 0 );
}

// ----------------------------------- //
Vector2D Vector2D::Left()
{
	return Vector2D( -1, 0 );
}

// ------------ OPERATORS ------------- //

// ----------------------------------- //
Vector2D & Vector2D::operator=( const Vector2D & other )
{
	x = other.x;
	y = other.y;

	return * this;
}

// ----------------------------------- //
Vector2D Vector2D::operator+( const Vector2D &other ) const
{
	return Vector2D( x + other.x, y + other.y );
}

// ----------------------------------- //
Vector2D Vector2D::operator-( const Vector2D &other ) const
{
	return Vector2D( x - other.x, y - other.y );
}

// ----------------------------------- //
Vector2D Vector2D::operator*( const Vector2D &other ) const
{
	return Vector2D( x * other.x, y * other.y );
}

// ----------- NON-MEMBERS ------------ //

// ----------------------------------- //
Vector2D operator*( const float scale, const Vector2D vector )
{
	return Vector2D( vector.x * scale, vector.y * scale );
}