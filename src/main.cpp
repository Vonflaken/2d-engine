#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC true

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA_6
	
	// Basic
	Scene* scene = new Scene();
	Sprite* sptAlien = scene->CreateSprite( resourceManager.LoadImage( "data/anims/alienanim.png", 8, 1 ) );
	sptAlien->SetFPS( 16 );
	sptAlien->GetImage()->SetMidHandle();
	sptAlien->SetScale( 4, 4 );
	sptAlien->SetPosition( 400, 300 );
	// Advanced
	SkeletonSprite* sptBones = new SkeletonSprite( "data/anims/animation.xml" );
	sptBones->SetFPS( 32 );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		// FIXME: Dejar que el ResourceManager se haga cargo de liberar recursos( imágenes... ). Cambiar sistema de referencias a una imagen y poner punteros a null ( o 0 ) en vez de delete
		renderer.SetBlendMode( renderer.ALPHA );
		
		int8 axeX = screen.GetAxis( "horizontal" );
		int8 axeY = screen.GetAxis( "vertical" );
		if ( BASIC )
		{
			sptAlien->RotateTo( 35 * axeX, 100 );
			sptAlien->SetPosition( sptAlien->GetX() + axeX, sptAlien->GetY() + axeY );
		}
		else
		{
			sptBones->SetPosition( screen.GetMouseX(), screen.GetMouseY() );
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