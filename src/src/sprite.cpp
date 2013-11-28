#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image, double colx, double coly, double colwidth, double colheight, 
		uint16 firstFrame, uint16 lastFrame, uint8 r, uint8 g, uint8 b, uint8 a ) {
	// TAREA: Implementar
	this->image = image;
	x = 0.00;
	y = 0.00;
	z = 0.00;
	this->colx = colx;
	this->coly = coly;
	this->colwidth = colwidth;
	this->colheight = colheight;
	if ( colwidth == 0.00 )
	{
		this->colwidth = this->image->GetWidth();
	}
	if ( colheight == 0.00 )
	{
		this->colheight = this->image->GetHeight();
	}
	angle = 0.00;
	scalex = 1.00;
	scaley = 1.00;
	radius = colwidth / 2;
	animFPS = 25;
	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	currentFrame = this->firstFrame;
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

Sprite::~Sprite() {
    delete image;
}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
	return false;
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
	return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar

}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada

	// TAREA: Actualizar movimiento animado

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().DrawImage( image, x, y, currentFrame, image->GetWidth() * scalex, image->GetHeight() * scaley, angle );
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}