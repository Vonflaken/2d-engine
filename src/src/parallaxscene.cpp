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
	autoBackPosX = autoBackPosY = 0.00;
	autoFrontPosX = autoFrontPosY = 0.00;
}

void ParallaxScene::Update( double elapsed, Map * map )
{
	Scene::Update( elapsed, map );

	autoBackPosX += autoBackSpeedX * elapsed;
	autoBackPosY += autoBackSpeedY * elapsed;
	backX = autoBackPosX + GetCamera().GetX() * relBackSpeedX;
	backY = autoBackPosY + GetCamera().GetY() * relBackSpeedY;

	autoFrontPosX += autoFrontSpeedX * elapsed;
	autoFrontPosY += autoFrontSpeedY * elapsed;
	frontX = autoFrontPosX + GetCamera().GetX() * relFrontSpeedX;
	frontY = autoFrontPosY + GetCamera().GetY() * relFrontSpeedY;
}

void ParallaxScene::RenderBackground() const
{
	if ( backLayer )
		Renderer::Instance().DrawTiledImage( backLayer, 0.00, 0.00, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), backX, backY );

	if ( frontLayer )
		Renderer::Instance().DrawTiledImage( frontLayer, 0.00, 0.00, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), frontX, frontY );
}