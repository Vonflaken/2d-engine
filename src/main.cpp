#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC true

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA DE INTERFAZ GRÁFICA - InputManager
	InputManager & inputManager = InputManager::Instance();

	inputManager.CreateVirtualButton( eAction::UP, GLFW_KEY_UP );
	inputManager.CreateVirtualButton( eAction::RIGHT, GLFW_KEY_RIGHT );
	inputManager.CreateVirtualButton( eAction::DOWN, GLFW_KEY_DOWN );
	inputManager.CreateVirtualButton( eAction::LEFT, GLFW_KEY_LEFT );
	inputManager.CreateVirtualButton( eAction::JUMP, GLFW_KEY_SPACE );

	// PRÁCTICA_8
	int8 axeX = 0;
	int8 axeY = 0;
	// Image * imgBackground = resourceManager.LoadImage( "data/images/background.png" );
	// Scene * scene = new Scene( imgBackground );
	Image * imgBack = resourceManager.LoadImage( "data/images/backlayer.png" );
	Image * imgFront = resourceManager.LoadImage( "data/images/frontlayer.png" );
	ParallaxScene * scene = new ParallaxScene( imgBack, imgFront );
	scene->SetAutoBackSpeed( 32.00, 32.00 );
	scene->SetRelativeBackSpeed( 0.8, 0.8 );
	scene->SetAutoFrontSpeed( -32.00, 32.00 );
	scene->SetRelativeFrontSpeed( 1.00, 1.00 );
	Camera & camera = scene->GetCamera();
	Sprite * sptAlien = scene->CreateSprite( resourceManager.LoadImage( "data/images/alien.png" ) );
	sptAlien->GetImage()->SetMidHandle();
	sptAlien->SetPosition( screen.GetWidth() / 2, screen.GetHeight() / 2 );
	camera.FollowSprite( sptAlien );
	// camera.SetBounds( 0.00, 0.00, imgBackground->GetWidth(), imgBackground->GetHeight() );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		renderer.SetBlendMode( Renderer::ALPHA );
		
		// PRÁCTICA DE INTERFAZ GRÁFICA - InputManager

		/*
		screen.SetTitle( "idle" );
		if ( inputManager.GetActionState( eAction::UP ) )
		{
			sptAlien->MoveTo( sptAlien->GetX(), sptAlien->GetY() - 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::RIGHT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() + 1, sptAlien->GetY(), 25.00 );
		}
		if ( inputManager.GetActionState( eAction::UP ) && inputManager.GetActionState( eAction::RIGHT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() + 1, sptAlien->GetY() - 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::DOWN ) )
		{
			sptAlien->MoveTo( sptAlien->GetX(), sptAlien->GetY() + 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::DOWN ) && inputManager.GetActionState( eAction::RIGHT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() + 1, sptAlien->GetY() + 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::LEFT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() - 1, sptAlien->GetY(), 25.00 );
		}
		if ( inputManager.GetActionState( eAction::UP ) && inputManager.GetActionState( eAction::LEFT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() - 1, sptAlien->GetY() - 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::DOWN ) && inputManager.GetActionState( eAction::LEFT ) )
		{
			sptAlien->MoveTo( sptAlien->GetX() - 1, sptAlien->GetY() + 1, 25.00 );
		}
		if ( inputManager.GetActionState( eAction::JUMP ) )
		{
			screen.SetTitle( "jump" );
		}
		*/

		axeX = screen.GetAxis( "horizontal" );
		axeY = screen.GetAxis( "vertical" );

		if ( BASIC )
		{
			sptAlien->MoveTo( sptAlien->GetX() + axeX, sptAlien->GetY() + axeY, 200.00 );
			scene->Update( screen.ElapsedTime() );
			scene->Render();
		}
		else
		{
			
		}

		// inputManager.Update();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	resourceManager.FreeResources();

	return 0;
}