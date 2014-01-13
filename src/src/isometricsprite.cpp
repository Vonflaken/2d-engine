#include "../include/isometricsprite.h"
#include "../include/math.h"
#include "../include/image.h"

void IsometricSprite::SetCollision( CollisionMode mode )
{
	if ( mode == COLLISION_PIXEL )
		Sprite::SetCollision( COLLISION_RECT );
	else
		Sprite::SetCollision( mode );
}

void IsometricSprite::Update( double elapsed, const Map* map )
{
	Sprite::Update( elapsed, map );

	TransformIsoCoords( GetX(), GetY(), GetZ(), &screenX, &screenY );
}

void IsometricSprite::UpdateCollisionBox()
{
	double cx = GetX() - GetImage()->GetHandleX() * fabs( GetScaleX() );
	double cy = GetY() - GetImage()->GetHandleX() * fabs( GetScaleX() );
	double cw = GetImage()->GetWidth() * fabs( GetScaleX() );
	double ch = GetImage()->GetWidth() * fabs( GetScaleX() );
	Sprite::UpdateCollisionBox( cx, cy, cw, ch );
}