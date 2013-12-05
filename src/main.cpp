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

	renderer.SetBlendMode( renderer.ALPHA );
	Sprite * sptAlien = new Sprite( resourceManager.LoadImage( "data/alien.png" ) );
	sptAlien->SetPosition( 250.00, 250.00 );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{	
		renderer.Clear();
		
		// PRÁCTICA DE INTERFAZ GRÁFICA - InputManager

		sptAlien->Render();

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

		sptAlien->Update( screen.ElapsedTime() );
		inputManager.Update();

		if ( BASIC )
		{
			
		}
		else
		{
			
		}

		// Refrescamos la pantalla
		screen.Refresh();
	}

	return 0;
}