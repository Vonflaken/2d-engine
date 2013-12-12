#include "../include/camera.h"
#include "../include/sprite.h"

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

void Camera::SetX( double x )
{
	if ( !HasBounds() )
	{
		this->x = x;
	}
	else
	{
		if ( x < GetMinX() )
		{
			this->x = GetMinX();
		}
		else if ( x > GetMaxX() )
		{
			this->x = GetMaxX();
		}
		else
		{
			this->x = x;
		}
	}
}

void Camera::SetY( double y )
{
	if ( !HasBounds() )
	{
		this->y = y;
	}
	else
	{
		if ( y < GetMinY() )
		{
			this->y = GetMinY();
		}
		else if ( y > GetMaxY() )
		{
			this->y = GetMaxY();
		}
		else
		{
			this->y = y;
		}
	}
}

void Camera::Update()
{
	if ( followingSprite )
	{
		SetPosition( followingSprite->GetScreenX() - Screen::Instance().GetWidth() / 2, 
			followingSprite->GetScreenY() - Screen::Instance().GetHeight() / 2 );
	}
}