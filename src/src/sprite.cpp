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

Sprite::Sprite(Image* image, double colx, double coly, double colwidth, double colheight, 
		uint16 firstFrame, uint16 lastFrame, uint8 r, uint8 g, uint8 b, uint8 a )
{
	this->image = image;
	this->image->AddReference();
	x = 0.00;
	y = 0.00;
	z = 0.00;
	this->colx = colx;
	this->coly = coly;
	this->colwidth = colwidth;
	this->colheight = colheight;
	angle = 0.00;
	scalex = 1.00;
	scaley = 1.00;
	radius = image->GetWidth() / 2;
	animFPS = 25;
	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	currentFrame = this->firstFrame;
	nextFrameTimer = 0;
	blendMode = Renderer::BlendMode::ALPHA;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	collision = NULL;
	colPixelData = NULL;
	colSprite = NULL;
	collided = false;
	rotating = false;
	toAngle = 0;
	rotatingSpeed = animFPS;
	deegresToRotate = 0.00;
	moving = false;
	toX = 0.00;
	toY = 0.00;
	movingSpeedX = animFPS;
	movingSpeedY = animFPS;
	prevX = x;
	prevY = y;
}

Sprite::~Sprite()
{
	image->RemoveReference();
	delete collision;
    // image = 0;
}

void Sprite::SetCollision(CollisionMode mode) {
	delete collision;

	switch( mode )
	{
		case COLLISION_NONE:
			collision = 0;
			break;
		case COLLISION_CIRCLE:
			collision = new CircleCollision( &x, &y, &radius );
			break;
		case COLLISION_RECT:
			collision = new RectCollision( &colx, &coly, &colwidth, &colheight );
			break;
		case COLLISION_PIXEL:
			// collision = new CollisionPixelData( this->image->GetFilename() );
			break;
	}
}

bool Sprite::CheckCollision(Sprite* sprite) {
	const Collision * otherCollision = sprite->collision;
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
	if ( map && map->CheckCollision( collision ) )
		return true;

	return false;
}

void Sprite::RotateTo( double angle, double speed )
{

	if ( ( toAngle > angle ) ? ( toAngle - angle ) > EPSILON : 
		( angle - toAngle ) > EPSILON )
	{
		toAngle = ( uint16 ) DEG360 * ceil( LogWithBase( DEG360, abs( angle ) ) - angle );
		deegresToRotate = ( angle - this->angle < this->angle - angle ) ? angle - this->angle : 
			abs( this->angle - angle );
	}

	if ( abs( deegresToRotate ) > EPSILON )
	{
		// Rotating
		rotatingSpeed = speed;

		rotating = true;
	}
	else
	{
		// Not rotating
		rotating = false;
	}
}

void Sprite::MoveTo( double x, double y, double speedX, double speedY )
{
	if ( speedY < EPSILON )
	{
		speedY = speedX;
	}

	toX = x;
	toY = y;
	double distance = ( double ) Vector2D::Distance( Vector2D( this->x, this->y ), 
			Vector2D( ( float ) x, ( float ) y ) );

	if ( distance > EPSILON )
	{
		// Set direction at x axe
		if ( this->x < x )
		{
			movingSpeedX = speedX;
			// Bug fixed: when right action backs to false the program flow go into next 'else if' check so 'movingSpeedX' get negative sign
			if ( sgn( movingSpeedX ) < 0 )
			{
				movingSpeedX *= - 1;
			}
		}
		else if ( this->x > x )
		{
			movingSpeedX = speedX * -1;
		}
		else
		{
			movingSpeedX = 0.00;
		}

		// Set direction at y axe
		if ( this->y < y )
		{
			movingSpeedY = speedY;
		}
		else if ( this->y > y )
		{
			movingSpeedY = speedY * -1;
		}
		else
		{
			movingSpeedY = 0.00;
		}

		moving = true;
	}
	else
	{
		moving = false;
	}
}

void Sprite::Update( double elapsed, const Map* map )
{
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	nextFrameTimer += animFPS * elapsed;
	if ( nextFrameTimer > 1 )
	{
		currentFrame++;
		nextFrameTimer = 0;
	}

	if ( rotating )
	{
		if ( sgn( deegresToRotate ) > 0.00 )
		{
			angle += rotatingSpeed * elapsed; // Update clockwise rotate
			deegresToRotate -= rotatingSpeed * elapsed; // Update deegres left to reach toAngle
		}
		else
		{
			angle -= rotatingSpeed * elapsed; // Update counterclockwise rotate
			deegresToRotate += rotatingSpeed * elapsed; // Update deegres left to reach toAngle
		}

		RotateTo( toAngle, rotatingSpeed );
	}

	if ( moving )
	{
		prevX = x;
		prevY = y;

		x += movingSpeedX * elapsed;
		UpdateCollisionBox();
		if ( CheckCollision( map ) )
			x = prevX;
		y += movingSpeedY * elapsed;
		UpdateCollisionBox();
		if ( CheckCollision( map ) )
			y = prevY;

		if ( prevX == x && prevY == y )
			moving = false;
		else
			MoveTo( toX, toY, movingSpeedX, movingSpeedY );
	}

	// Informacion final de colision
	UpdateCollisionBox();
	CheckCollision( map );
}

void Sprite::Render() const
{
	Renderer::Instance().SetBlendMode( blendMode );
	Renderer::Instance().SetColor( GetRed(), GetGreen(), GetBlue(), GetAlpha() );
	Renderer::Instance().DrawImage( image, x, y, currentFrame, image->GetWidth() * scalex, image->GetHeight() * scaley, WrapValue( angle, DEG360 ) );
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