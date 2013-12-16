#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC true

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();
	Scene * scene = new Scene();

	screen.Open(800, 600, false);

	// PRÁCTICA_9
	
	Sprite * imgStar = scene->CreateSprite( new Image( "data/images/star.png" ) );
	Emitter * emitter = scene->CreateEmitter( new Image( "data/images/star.png" ), true );

	emitter->SetRate( 500, 1000 );
	emitter->SetVelocityX( -128, 128 );
	emitter->SetVelocityY( -128, 128 );
	emitter->SetAngularVelocity( 0, 360 );
	emitter->SetLifetime( 1, 2 );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		if ( BASIC )
		{
			emitter->SetPosition( screen.GetMouseX(), screen.GetMouseY() );
			imgStar->SetPosition( screen.GetMouseX(), screen.GetMouseY() );

			if ( glfwGetMouseButton( 0 ) )
				emitter->Start();
			else
				emitter->Stop();
		}
		else
		{
			
		}

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();

	return 0;
}