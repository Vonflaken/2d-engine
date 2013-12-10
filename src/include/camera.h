#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "math.h"
#include <stdio.h>

class Sprite;

class Camera
{
public:
	Camera();
	// Camera( double x, double y, Sprite * sprite = NULL, double xy0 = 0.00, double by0 = 0.00, double xy1 = 0.00, double by1 = 0.00 );

	virtual void SetPosition( double x, double y ) { this->x = x; this->y = y; }
	virtual void SetX( double x ) { this->x = x; }
	virtual void SetY( double y ) { this->y = y; }
	virtual double GetX() const { return x; }
	virtual double GetY() const { return y; }

	virtual void SetBounds( double bx0, double by0, double bx1, double by1 ) { boundx0 = bx0; boundy0 = by0; boundx1 = bx1; boundy1 = by1; }
	virtual bool HasBounds() const { if ( ( boundx0 - boundx1 ) <= EPSILON ) { return false; } return true; }
	virtual double GetMinX() const { return boundx0; }
	virtual double GetMinY() const { return boundy0; }
	virtual double GetMaxX() const { return boundx1; }
	virtual double GetMaxY() const { return boundy1; }

	virtual void FollowSprite( Sprite * sprite ) { followingSprite = sprite; }

	virtual void Update();

private:
	double x, y;
	double boundx0, boundy0, boundx1, boundy1;
	Sprite * followingSprite;
};

#endif