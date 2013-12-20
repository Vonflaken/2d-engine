#ifndef UGINE_PIXELCOLLISION_H
#define UGINE_PIXELCOLLISION_H

#include "collision.h"
#include "collisionmanager.h"

class PixelCollision : public Collision {
public:
	PixelCollision( double* x, double* y, CollisionPixelData* pixels ) : x(x), y(y), pixels(pixels) {}

    virtual bool DoesCollide( const Collision* other ) const { return other->DoesCollide( pixels, *x, *y ); }
	virtual bool DoesCollide( CollisionPixelData* p2, double x2, double y2 ) const { return CollisionManager::Instance().PixelsToPixels( pixels, *x, *y, p2, x2, y2 ); }
    virtual bool DoesCollide( double rx, double ry, double rwidth, double rheight ) const { return CollisionManager::Instance().PixelsToRect( pixels, *x, *y, rx, ry, rwidth, rheight ); }
    virtual bool DoesCollide( double radius, double cx, double cy ) const { return CollisionManager::Instance().CircleToPixels( cx, cy, radius, pixels, *x, *y ); }

private:
    double* x;
    double* y;
	CollisionPixelData* pixels;
};

#endif
