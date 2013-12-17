#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H

#include "vector2d.h"
#include "array.h"
// FIXME: Solo utilizar dos puntos para delimitar la region
class Particle;

class Affector
{
public:
	struct Region
	{
	public:
		Region() {}

		void SetRegion( Vector2D tl, Vector2D tr, Vector2D bl, Vector2D br ) { topLeft = tl; topRight = tr; bottomLeft = bl; bottomRight = br; }

		Vector2D topLeft;
		Vector2D topRight;
		Vector2D bottomLeft;
		Vector2D bottomRight;
	};

public:
	Affector( Vector2D tl, Vector2D tr, Vector2D bl, Vector2D br, uint8 minr, uint8 maxr, uint8 ming, uint8 maxg,
		uint8 minb, uint8 maxb, double minvelx, double maxvelx, double minvely, double maxvely, double minangvel, double maxangvel ) : 
		minr( minr ), maxr( maxr ), ming( ming ), maxg( maxg ), minb( minb ), maxb( maxb ), minvelx( minvelx ), maxvelx( maxvelx ), minvely( minvely ), maxvely( maxvely ), minangvel( minangvel ), maxangvel( maxangvel )
	{
		region.SetRegion( tl, tr, bl, br );
	}

	void AddParticle( Particle & particle ) { particles.Add( &particle ); } // GetParticles().Add( particle );
	bool IsParticleAffected( Particle & particle ) { for ( uint32 i = 0; i < particles.Size(); i++ ) if ( &particle == particles[ i ] ) return true; }
	void SetRegion( Vector2D tl, Vector2D tr, Vector2D bl, Vector2D br ) { region.SetRegion( tl, tr, bl, br ); }
	bool IsInsideRegion( double x, double y ) { if ( x > region.topLeft.x && x < region.bottomRight.x && y > region.topLeft.y && y < region.bottomRight.y ) return true; return false; }
	Vector2D GetTopLeft() { return region.topLeft; }
	Vector2D GetTopRight() { return region.topRight; }
	Vector2D GetBottomLeft() { return region.bottomLeft; }
	Vector2D GetBottomRight() { return region.bottomRight; }
	void SetMinColor( uint8 minr, uint8 ming, uint8 minb ) { this->minr = minr; this->ming = ming; this->minb = minb; }
	void SetMaxColor( uint8 maxr, uint8 maxg, uint8 maxb ) { this->maxr = maxr; this->maxg = maxg; this->maxb = maxb; }
	void SetMinRed( uint8 minr ) { this->minr = minr; }
	void SetMaxRed( uint8 maxr ) { this->maxr = maxr; }
	void SetMinGreen( uint8 ming ) { this->ming = ming; }
	void SetMaxGreen( uint8 maxg ) { this->maxg = maxg; }
	void SetMinBlue( uint8 minb ) { this->minb = minb; }
	void SetMaxBlue( uint8 maxb ) { this->maxb = maxb; }
	uint8 GetMinRed() { return minr; }
	uint8 GetMaxRed() { return maxr; }
	uint8 GetMinGreen() { return ming; }
	uint8 GetMaxGreen() { return maxg; }
	uint8 GetMinBlue() { return minb; }
	uint8 GetMaxBlue() { return maxb; }
	void SetMinVelX( double velx ) { minvelx = velx; }
	void SetMaxVelX( double velx ) { maxvelx = velx; }
	void SetMinVelY( double vely ) { minvely = vely; }
	void SetMaxVelY( double vely ) { maxvely = vely; }
	double GetMinVelX() { return minvelx; }
	double GetMaxVelX() { return maxvelx; }
	double GetMinVelY() { return minvely; }
	double GetMaxVelY() { return maxvely; }
	void SetMinAngVel( double angvel ) { minangvel = angvel; }
	void SetMaxAngVel( double angvel ) { maxangvel = angvel; }
	double GetMinAngVel() { return minangvel; }
	double GetMaxAngVel() { return maxangvel; }

private:
	Region region;
	Array< Particle * > particles;
	uint8 minr, maxr, ming, maxg, minb, maxb;
	double minvelx, maxvelx, minvely, maxvely;
	double minangvel, maxangvel;
};

#endif