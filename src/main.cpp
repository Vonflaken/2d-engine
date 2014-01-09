#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PR�CTICA_6
	
	IsometricScene* isoScene = new IsometricScene( resourceManager.LoadIsometricMap( "data/maps/isometric.tmx" ) );
	isoScene->SetCamera( new Camera() );
	IsometricSprite* isoSprite = isoScene->CreateSprite( resourceManager.LoadImage( "data/anims/isoplayer.png", 8, 8 ) );
	isoSprite->SetCollision( Sprite::COLLISION_RECT );
	isoSprite->SetPosition( isoScene->GetMap()->GetTileWidth() * 1.5, isoScene->GetMap()->GetTileHeight() * 1.5 );
	isoScene->GetCamera().FollowSprite( isoSprite );

	bool leftPushed = false;
	bool rightPushed = false;
	bool upPushed = false;
	bool downPushed = false;

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		renderer.Clear();

		renderer.SetBlendMode( renderer.ALPHA );
		
		int8 axeX = screen.GetAxis( "horizontal" );
		int8 axeY = screen.GetAxis( "vertical" );
		if ( axeX < 0 && !leftPushed )
		{
			leftPushed = true;

			isoSprite->SetFrameRange( 0, 0 + 4 );
			isoSprite->SetCurrentFrame( 0 );
		}
		if ( axeX > 0 && !rightPushed )
		{
			leftPushed = true;

			isoSprite->SetFrameRange( 40, 40 + 4 );
			isoSprite->SetCurrentFrame( 40 );
		}
		if ( axeY < 0 && !upPushed )
		{
			leftPushed = true;

			isoSprite->SetFrameRange( 24, 24 + 4 );
			isoSprite->SetCurrentFrame( 24 );
		}
		if ( axeY > 0 && !downPushed )
		{
			leftPushed = true;

			isoSprite->SetFrameRange( 56, 56 + 4 );
			isoSprite->SetCurrentFrame( 56 );
		}
		isoSprite->SetPosition( isoSprite->GetX() + axeX, isoSprite->GetY() + axeY );

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();

	return 0;
}