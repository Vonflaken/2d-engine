#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const bool BASIC = true;

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA_6
	
	// Basic
	MapScene* scene = new MapScene( resourceManager.LoadMap( "data/maps/map.tmx" ), 0, 0 );
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
		renderer.Clear();

		renderer.SetBlendMode( renderer.ALPHA );
		
		int8 axeX = screen.GetAxis( "horizontal" );
		int8 axeY = screen.GetAxis( "vertical" );
		if ( BASIC )
		{
			sptAlien->RotateTo( 35 * -axeX, 100 );
			sptAlien->SetPosition( sptAlien->GetX() + axeX, sptAlien->GetY() + axeY );
			scene->Update( screen.ElapsedTime() );
			scene->Render();
		}
		else
		{
			if ( sptBones->GetCurrentFrame() == sptBones->GetLastFrame() )
				sptBones->SetCurrentFrame( 0 );
			sptBones->SetPosition( screen.GetMouseX(), screen.GetMouseY() );
			sptBones->Update( screen.ElapsedTime() );
			sptBones->Render();
		}

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();

	return 0;
}