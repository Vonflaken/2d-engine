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
	
	// Basic
	Image * imgStar = resourceManager.LoadImage( "data/images/star.png" );
	Sprite * sptStar = scene->CreateSprite( imgStar );
	sptStar->GetImage()->SetMidHandle();
	Emitter * emitter = scene->CreateEmitter( imgStar, true );

	emitter->SetRate( 500, 1000 );
	emitter->SetVelocityX( -128, 128 );
	emitter->SetVelocityY( -128, 128 );
	emitter->SetAngularVelocity( 0, 360 );
	emitter->SetLifetime( 1, 2 );
	// Advanced
	emitter->AddAffector( new Affector( Vector2D( 0, 0 ), Vector2D( 0, 0 ), Vector2D( 0, 0 ), Vector2D( screen.GetWidth() / 2, 
		screen.GetHeight() ), 0, 0, 0, 255, 255, 0, -128, 128, -128, 128, 0, 360 ) );
	emitter->AddAffector( new Affector( Vector2D( screen.GetWidth() / 2, 0 ), Vector2D( 0, 0 ), Vector2D( 0, 0 ), Vector2D( screen.GetWidth(), 
		screen.GetHeight() ), 0, 0, 0, 0, 255, 255, -128, 128, -128, 128, 360, 720 ) );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		screen.SetTitle( String::FromInt( imgStar->GetReferences() ) );
		if ( BASIC )
		{
			renderer.SetBlendMode( renderer.ALPHA );

			emitter->SetPosition( screen.GetMouseX(), screen.GetMouseY() );
			sptStar->SetPosition( screen.GetMouseX(), screen.GetMouseY() );

			if ( glfwGetMouseButton( 0 ) )
				emitter->Start();
			else
				emitter->Stop();

			scene->Update( screen.ElapsedTime() );
			scene->Render();
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