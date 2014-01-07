#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC true

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA_11
	
	// Basic
	MapScene* scene = new MapScene( resourceManager.LoadMap( "data/maps/map.tmx" ) );
	Camera* camera = new Camera();
	scene->SetCamera( camera );
	Sprite* sptAlien = scene->CreateSprite( resourceManager.LoadImage( "data/images/alien.png" ) );
	sptAlien->SetPosition( 400, 300 );
	scene->GetCamera().FollowSprite( sptAlien );
	scene->GetCamera().SetBounds( 0, 0, scene->GetMap()->GetWidth(), scene->GetMap()->GetHeight() );
	// Advanced

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		// FIXME: Dejar que el ResourceManager se haga cargo de liberar recursos( imágenes... ). Cambiar sistema de referencias a una imagen y poner punteros a null ( o 0 ) en vez de delete
		renderer.SetBlendMode( renderer.ALPHA );
		
		int8 axeX = screen.GetAxis( "horizontal" );
		int8 axeY = screen.GetAxis( "vertical" );
		if ( BASIC )
		{
			sptAlien->SetPosition( sptAlien->GetX() + axeX, sptAlien->GetY() + axeY );
		}
		else
		{
			
		}
		
		scene->Update( screen.ElapsedTime() );
		scene->Render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();

	return 0;
}