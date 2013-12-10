#include "../include/camera.h"
#include "../include/sprite.h"
#include "../include/screen.h"

Camera::Camera()
{
	x = 0.00;
	y = 0.00;
	boundx0 = 0.00;
	boundy0 = 0.00;
	boundx1 = 0.00;
	boundy1 = 0.00;
	followingSprite = NULL;
}
/*
Camera::Camera( double x, double y, Sprite * sprite, double bx0, double by0, double bx1, double by1 )
{
	this->x = x;
	this->y = y;
	followingSprite = sprite;
	boundx0 = bx0;
	boundy0 = by0;
	boundx1 = bx1;
	boundy1 = by1;
}
*/
void Camera::Update()
{
	if ( followingSprite != NULL )
	{
		// Follow sprite
		x = followingSprite->GetX() - Screen::Instance().GetWidth() / 2;
		y = followingSprite->GetY() - Screen::Instance().GetHeight() / 2;
	}

	if ( HasBounds() )
	{
		// Check limits
		if ( x > boundx0 && y > boundy0 && 
			x < boundx1 - Screen::Instance().GetWidth() && y < boundy1 - Screen::Instance().GetHeight() )
		{
			// Inside
			Screen::Instance().SetTitle( "Dentro de los límites" );
		}
		else
		{
			// Outside
			Screen::Instance().SetTitle( "Fuera de los límites" );
		}
	}
}