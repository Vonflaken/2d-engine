#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/vector2d.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image )
{
	this->image = image;
	SetPosition( 0, 0 );
	angle = 0;
	SetScale( 1.0f, 1.0f );
	radius = 0;
	animFPS = 0;
	SetFrameRange( 0, ( image ) ? image->GetNumFrames() - 1 : 0 );
	currentFrame = 0;
	nextFrameTimer = 0;
	blendMode = Renderer::ALPHA;
	SetColor( 255, 255, 255, 255 );
	collision = NULL;
	colPixelData = NULL;
	colSprite = NULL;
	collided = false;
	rotating = false;
	moving = false;
}

Sprite::~Sprite()
{
	if ( collision )
		delete collision;
    image = 0;
}

void Sprite::SetCollision( CollisionMode mode )
{
	if ( collision )
		delete collision;

	switch( mode )
	{
		case COLLISION_NONE:
			collision = NULL;
			break;
		case COLLISION_CIRCLE:
			collision = new CircleCollision( &x, &y, &radius );
			break;
		case COLLISION_RECT:
			collision = new RectCollision( &colx, &coly, &colwidth, &colheight );
			break;
		case COLLISION_PIXEL:
			// collision = new PixelCollision( colPixelData, &colx, &coly );
			break;
	}
}

bool Sprite::CheckCollision( Sprite* sprite )
{
	const Collision* otherCollision = sprite->GetCollision();
	if ( collision && otherCollision )
	{
		if ( collision->DoesCollide( sprite->collision ) )
		{
			colSprite = sprite;
			collided = true;
			sprite->colSprite = this;
			sprite->collided = true;

			return true;
		}
	}

	return false;
}

bool Sprite::CheckCollision( const Map* map )
{
	if ( collision && map && map->CheckCollision( collision ) )
	{
		collided = true;

		return true;
	}

	return false;
}

void Sprite::RotateTo( double angle, double speed )
{
	if ( WrapValue( angle, DEG360 ) == WrapValue( this->angle, DEG360 ) || speed == 0 )
	{
		// Stop rotating
		rotating = false;
	}
	else
	{
		// Still rotating
		rotating = true;
		toAngle = ( uint16 )WrapValue( angle, DEG360 );

		uint16 wrapAngle = ( uint16 )WrapValue( this->angle, DEG360 );
		if ( min( WrapValue( toAngle - wrapAngle, DEG360 ), WrapValue( wrapAngle - toAngle, DEG360 ) ) == WrapValue( toAngle - wrapAngle, DEG360 ) )
		{
			// Counter-clockwise
			rotatingSpeed = fabs( speed );
			deegresToRotate = WrapValue( toAngle - wrapAngle, DEG360 );
		}
		else
		{
			// Clockwise
			rotatingSpeed = -fabs( speed );
			deegresToRotate = WrapValue( wrapAngle - toAngle, DEG360);
		}
	}
}

void Sprite::MoveTo( double x, double y, double speedX, double speedY )
{
	if ( this->x == x  &&  this->y == y )
	{
		// Stop moving
		moving = false;
	}
	else
	{
		// Still moving
		moving = true;
		toX = x;
		toY = y;
		
		if ( speedY == 0 ) {
			double timeNeeded = Distance( this->x, this->y, x, y ) / fabs( speedX );
			movingSpeedX = fabs( this->x - x ) / timeNeeded;
			movingSpeedY = fabs( this->y - y ) / timeNeeded;
		}
		else
		{
			movingSpeedX = speedX;
			movingSpeedY = speedY;
		}
	}
}

void Sprite::Update( double elapsed, const Map* map )
{
	// Re-init collision data
	colSprite = NULL;
	collided = false;

	// Update frame animation
	nextFrameTimer += animFPS * elapsed;
	if ( nextFrameTimer > 1 )
	{
		currentFrame++;
		nextFrameTimer = 0;

		if ( currentFrame > lastFrame )
			currentFrame = firstFrame;
		if ( currentFrame < firstFrame )
			currentFrame = lastFrame;
	}

	// Update rotation
	if ( rotating )
	{
		angle += rotatingSpeed * elapsed;
		deegresToRotate -= fabs( rotatingSpeed * elapsed );

		if ( deegresToRotate <= 0 )
		{
			angle = toAngle;
			rotating = false;
		}
	}

	// Update movement
	if ( moving )
	{
		prevX = x;
		prevY = y;

		if ( x < toX )
		{
			// Right
			x += movingSpeedX * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision( map ) )
				x = prevX;
			if ( x > toX )
				x = toX;
		}
		else
		{
			// Left
			x -= movingSpeedX * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision( map ) )
				x = prevX;
			if ( x < toX )
				x = toX;
		}
		if ( y < toY )
		{
			// Down
			y += movingSpeedY * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision( map ) )
				y = prevY;
			if ( y > toY )
				y = toY;
		}
		else
		{
			// Up
			y -= movingSpeedY * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision( map ) )
				y = prevY;
			if ( y < toY )
				y = toY;
		}

		if ( ( x == prevX && y == prevY ) || ( x == toX && y == toY ) )
			moving = false;
	}

	// Update collision data
	UpdateCollisionBox();
}

void Sprite::Render() const
{
	/*
	// ---------- DEBUG COLLISION BOXES ----------- //
	Renderer::Instance().SetColor( 255, 0, 0, 255 );
	double screencolx, screencoly;
	TransformIsoCoords( colx, coly, 0, &screencolx, &screencoly );
	Renderer::Instance().DrawParallelogram( screencolx, screencoly, 0, 0, colwidth, colheight );
	// --------------------------------------------//
	*/
	Renderer::Instance().SetBlendMode( blendMode );
	Renderer::Instance().SetColor( GetRed(), GetGreen(), GetBlue(), GetAlpha() );
	Renderer::Instance().DrawImage( image, GetScreenX(), GetScreenY(), currentFrame, image->GetWidth() * scalex, image->GetHeight() * scaley, angle );
}

void Sprite::UpdateCollisionBox() {
	double cx = x - image->GetHandleX() * fabs( scalex );
	double cy = y - image->GetHandleY() * fabs( scaley );
	double cw = image->GetWidth() * fabs( scalex );
	double ch = image->GetHeight() * fabs( scaley );
	UpdateCollisionBox( cx, cy, cw, ch );
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	colx = x;
	coly = y;
	colwidth = w;
	colheight = h;
}