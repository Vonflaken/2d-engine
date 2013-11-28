#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC false

int main(int argc, char* argv[])
{
	Screen &screen = Screen::Instance();
	const Renderer &renderer = Renderer::Instance();

	screen.Open(800, 600, false);


	// ------------- BASIC ------------- //
	const double degps = 30.00;
	double currDeg = 0.00;

	double scaleps = 2.00;
	double currScale = 1.00;
	const double maxScale = 5.00;
	const double minScale = 0.50;

	Image *imgSoccerBall = new Image( "data/soccer_npot.png" );
	Sprite *sptSoccerBall = new Sprite( imgSoccerBall );
	sptSoccerBall->SetPosition( screen.GetWidth() / 2 - sptSoccerBall->GetImage()->GetWidth(), screen.GetHeight() / 2 );

	Image *imgBasketBall = new Image( "data/ball.png" );
	Sprite *sptBasketBall = new Sprite( imgBasketBall );
	sptBasketBall->SetPosition( screen.GetWidth() / 2 + sptBasketBall->GetImage()->GetWidth(), screen.GetHeight() / 2 );

	// ------------- ADVANCED ------------- //
	double speed = 2.00;
	double toAngle = 15.00;

	Image *imgAlien = new Image( "data/alien.png" );
	Sprite *sptAlien = new Sprite( imgAlien );
	sptAlien->SetPosition( screen.GetWidth() / 2, screen.GetHeight() / 2 );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) ) {

		currDeg += degps * screen.ElapsedTime();
		currScale += scaleps * screen.ElapsedTime();
		if ( currScale >= maxScale )
		{
			scaleps *= -1;
		}
		else if ( currScale <= minScale )
		{
			scaleps *= -1;
		}

		renderer.Clear();

		if ( BASIC )
		{
			sptSoccerBall->SetAngle( currDeg );
			sptSoccerBall->SetScale( currScale, currScale );
			renderer.SetBlendMode( sptSoccerBall->GetBlendMode() );
			sptSoccerBall->Render();

			sptBasketBall->SetAngle( currDeg );
			sptBasketBall->SetScale( currScale, currScale );
			renderer.SetBlendMode( sptBasketBall->GetBlendMode() );
			sptBasketBall->Render();
		}
		else
		{
			renderer.SetBlendMode( sptAlien->GetBlendMode() );
			sptAlien->Update( screen.ElapsedTime() );
			sptAlien->Render();

			sptAlien->MoveTo( screen.GetMouseX(), screen.GetMouseY(), speed, speed ); // Move to cursor

			if ( screen.KeyPressed( GLFW_KEY_LEFT ) )
			{
				// Rotate to left
				sptAlien->RotateTo( -toAngle, speed );
			}
			else if ( screen.KeyPressed( GLFW_KEY_RIGHT ) )
			{
				// Rotate to right
				sptAlien->RotateTo( toAngle, speed );
			}
		}

		// Refrescamos la pantalla
		screen.Refresh();
	}

	return 0;
}