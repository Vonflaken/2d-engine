#include "../include/parallaxscene.h"
#include "../include/renderer.h"

ParallaxScene::ParallaxScene( Image * imgBack, Image * imgFront )
{
	backLayer = imgBack;
	frontLayer = imgFront;
	
	backX = backY = 0.00;
	frontX = frontY = 0.00;
	relBackSpeedX = relBackSpeedY = 0.00;
	relFrontSpeedX = relFrontSpeedY = 0.00;
	autoBackSpeedX = autoBackSpeedY = 0.00;
	autoFrontSpeedX = autoFrontSpeedY = 0.00;
}

void ParallaxScene::Update( double elapsed, Map * map )
{
	Scene::Update( elapsed, map );
	
	backX = autoBackSpeedX * elapsed + GetCamera().GetX() * relBackSpeedX;
	backY = autoBackSpeedY * elapsed + GetCamera().GetY() * relBackSpeedY;

	frontX = autoFrontSpeedX * elapsed + GetCamera().GetX() * relFrontSpeedX;
	frontY = autoFrontSpeedY * elapsed + GetCamera().GetY() * relFrontSpeedY;
}

void ParallaxScene::RenderBackground() const
{
	Renderer::Instance().DrawTiledImage( backLayer, 0.00, 0.00, Screen::Instance().GetWidth(), 
		Screen::Instance().GetHeight(), backX, backY );

	Renderer::Instance().DrawTiledImage( frontLayer, 0.00, 0.00, Screen::Instance().GetWidth(), 
		Screen::Instance().GetHeight(), frontX, frontY );
}