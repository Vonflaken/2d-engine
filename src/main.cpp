#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA_12
	
	double screenX = 0.0;
	double screenY = 0.0;

	IsometricMap* isoMap = resourceManager.LoadIsometricMap( "data/maps/isometric.tmx", 11 );
	IsometricScene* isoScene = new IsometricScene( isoMap );
	IsometricSprite* isoSprite = isoScene->CreateSprite( resourceManager.LoadImage( "data/anims/isoplayer.png", 8, 8 ) );
	isoSprite->SetCollision( Sprite::COLLISION_RECT );
	TransformIsoCoords( isoScene->GetMap()->GetTileWidth() * 1.5, isoScene->GetMap()->GetTileHeight() * 1.5, 0.0, &screenX, &screenY );
	isoSprite->SetPosition( screenX, screenY );
	isoScene->GetCamera().FollowSprite( isoSprite );
	bool leftPushed = false;
	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		renderer.Clear();

		renderer.SetBlendMode( renderer.ALPHA );

		int8 axeX = screen.GetAxis( "horizontal" );
		int8 axeY = screen.GetAxis( "vertical" );
		if ( glfwGetKey( GLFW_KEY_LEFT ) && !leftPushed )
		{
			leftPushed = true;
			isoSprite->SetFrameRange( 0, 0 + 4 );
			isoSprite->SetCurrentFrame( 0 );
		}
		if ( glfwGetKey( GLFW_KEY_RIGHT ) )
		{
			isoSprite->SetFrameRange( 40, 40 + 4 );
			isoSprite->SetCurrentFrame( 40 );
		}
		if ( glfwGetKey( GLFW_KEY_UP ) )
		{
			isoSprite->SetFrameRange( 24, 24 + 4 );
			isoSprite->SetCurrentFrame( 24 );
		}
		if ( glfwGetKey( GLFW_KEY_DOWN ) )
		{
			isoSprite->SetFrameRange( 56, 56 + 4 );
			isoSprite->SetCurrentFrame( 56 );
		}
		if ( axeY == 0 && axeX == 0 )
		{
			isoSprite->SetFPS( 0 );
			leftPushed = false;
		}
		else
			isoSprite->SetFPS( 30 );

		//TransformIsoCoords( isoSprite->GetScreenX() + axeX, isoSprite->GetScreenY() + axeY, 0.0, &screenX, &screenY );
		//isoSprite->SetPosition( screenX, screenY );

		isoScene->Update( screen.ElapsedTime(), isoMap );
		isoScene->Render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();

	return 0;
}