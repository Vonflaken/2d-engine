#include "../include/particle.h"
#include "../include/math.h"
#include <math.h>

Particle::Particle() : Sprite( 0 )
{
	velocityx, velocityy = 0;
	angularVelocity = 0;
	lifetime = 0;
	initialLifetime = 0;
	autofade = false;
}

Particle::Particle( Image * image, double velx, double vely, double angularVel, 
	double lifetime, bool autofade ) : Sprite( image )
{
	velocityx = velx;
	velocityy = vely;
	angularVelocity = angularVel;
	this->lifetime = abs( lifetime );
	initialLifetime = this->lifetime;
	this->autofade = autofade;
}

void Particle::Update( double elapsed )
{
	Sprite::Update( elapsed );

	lifetime = Clamp( lifetime - elapsed, initialLifetime, 0.00 );

	SetX( GetX() + velocityx * elapsed );
	SetY( GetY() + velocityy * elapsed );
	SetAngle( GetAngle() + angularVelocity * elapsed );

	if ( autofade )
		SetColor( GetRed(), GetGreen(), GetBlue(), ( uint8 ) ( lifetime * 255 / initialLifetime ) );
}