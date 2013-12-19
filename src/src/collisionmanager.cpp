#include "../include/collisionmanager.h"
#include "../include/math.h"

CollisionManager *CollisionManager::manager = 0;

const CollisionManager & CollisionManager::Instance()
{
	if ( !manager )
		manager = new CollisionManager();

	return * manager;
}

bool CollisionManager::CircleToCircle( double x1, double y1, double r1, double x2, double y2, double r2 ) const
{
	double gap = Distance( x1, y1, x2, y2 );
	if ( gap <= r1 + r2 )
		return true;

	return false;
}

bool CollisionManager::CircleToPixels( double cx, double cy, double cr, const CollisionPixelData * pixels, double px, double py ) const
{
	return false;
}

bool CollisionManager::CircleToRect( double cx, double cy, double cr, double rx, double ry, double rw, double rh ) const
{
	double lookatx = 0;
	double lookaty = 0;
	ClosestPointToRect( cx, cy, rx, ry, rw, rh, &lookatx, &lookaty );
	if ( Distance( cx, cy, lookatx, lookaty ) < cr )
		return true;

	return false;
}

bool CollisionManager::PixelsToPixels( const CollisionPixelData * p1, double x1, double y1, const CollisionPixelData * p2, double x2, double y2 ) const
{
	return false;
}

bool CollisionManager::PixelsToRect( const CollisionPixelData * pixels, double px, double py, double rx, double ry, double rw, double rh ) const
{
	return false;
}

bool CollisionManager::RectToRect( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2 ) const
{
	return RectsOverlap( x1, y1, w1, h1, x2, y2, w2, h2 );
}