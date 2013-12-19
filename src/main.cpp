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
	Sprite *sptBall = scene->CreateSprite( resourceManager.LoadImage( "data/images/ball.png" ) );
	sptBall->SetCollision( Sprite::COLLISION_CIRCLE );
	sptBall->SetRadius( sptBall->GetImage()->GetWidth() / 2 );
	sptBall->SetPosition( 150, 150 );
	sptBall->GetImage()->SetMidHandle();
	Sprite *sptBox = scene->CreateSprite( resourceManager.LoadImage( "data/images/box.jpg" ) );
	sptBox->SetCollision( Sprite::COLLISION_RECT );
	sptBox->SetPosition( screen.GetWidth() - 150, screen.GetHeight() - 150 );
	sptBox->GetImage()->SetMidHandle();
	Sprite *sptPointerCircle = scene->CreateSprite( resourceManager.LoadImage( "data/images/circle.png" ) );
	sptPointerCircle->SetCollision( Sprite::COLLISION_CIRCLE );
	sptPointerCircle->SetRadius( sptPointerCircle->GetImage()->GetWidth() / 2 );
	sptPointerCircle->GetImage()->SetMidHandle();
	Sprite *sptPointerBox = scene->CreateSprite( resourceManager.LoadImage( "data/images/rect.png" ) );
	sptPointerBox->SetCollision( Sprite::COLLISION_RECT );
	sptPointerBox->GetImage()->SetMidHandle();
	sptPointerBox->SetPosition( 9999, 9999 );
	Sprite *activePointer = sptPointerCircle;
	// Advanced

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		// FIXME: Dejar que el ResourceManager se haga cargo de liberar recursos( imágenes... ). Cambiar sistema de referencias a una imagen y poner punteros a null ( o 0 ) en vez de delete
		//screen.SetTitle( String::FromInt( activePointer->DidCollide() ) );
		renderer.SetBlendMode( renderer.ALPHA );
		
		if ( BASIC )
		{
			if ( screen.MouseButtonPressed( 0 ) )
			{
				activePointer = sptPointerCircle;
				sptPointerBox->SetPosition( 9999, 9999 );
			}
			if ( screen.MouseButtonPressed( 1 ) )
			{
				activePointer = sptPointerBox;
				sptPointerCircle->SetPosition( 9999, 9999 );
			}
			activePointer->SetPosition( screen.GetMouseX(), screen.GetMouseY() );
			if ( activePointer->DidCollide() )
			{
				if ( activePointer->CollisionSprite() == sptBall )
					sptBall->SetColor( 255, 0, 0, 255 );
				if ( activePointer->CollisionSprite() == sptBox )
					sptBox->SetColor( 255, 0, 0, 255 );
				activePointer->SetColor( 255, 0, 0, 255 );
			}
			else
			{
				sptBox->SetColor( 255, 255, 255, 255 );
				sptBall->SetColor( 255, 255, 255, 255 );
				activePointer->SetColor( 255, 255, 255, 255 );
			}
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