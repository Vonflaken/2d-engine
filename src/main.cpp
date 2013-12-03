#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#include "Windows.h"
#include "xinput.h"

#pragma comment(lib, "XInput9_1_0.lib" )

#define BASIC false

int main(int argc, char* argv[])
{
	Screen &screen = Screen::Instance();
	const Renderer &renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// PRÁCTICA_5
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
	double speed = 15.00;
	double toAngle = 15;

	Image *imgAlien = new Image( "data/alien.png" );
	Sprite *sptAlien = new Sprite( imgAlien );
	sptAlien->SetPosition( screen.GetWidth() / 2, screen.GetHeight() / 2 );
	

	// PRÁCTICA_7
	// ------------- BASIC ------------- //
	Font * fontMonospaced = resourceManager.LoadFont( "data/monospaced.png" );
	String text = "Hola, mundo";
	int32 textWidth = text.Length() * fontMonospaced->GetWidth();
	float textSpeedX = Random( 128.0, 255.0 );
	float textSpeedY = Random( 128.0, 255.0 );
	Vector2D textPos( ( float ) screen.GetWidth() / 2, ( float ) screen.GetHeight() / 2 ); 

	// ------------- ADVANCED ------------- //
	Font * fontArial = resourceManager.LoadFont( "data/arial16.png" );

	// PRÁCTICA_2 de Interfaz de Usuario - Implementar InputManager
	InputManager::Instance().CreateVirtualButton( LEFT, GLFW_KEY_LEFT );
	InputManager::Instance().Update();

	double posx = screen.GetWidth() / 2;
	double posy = screen.GetHeight() / 2;

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) ) {

		// PRÁCTICA_5
		
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
			XINPUT_STATE state;
			ZeroMemory( &state, sizeof( XINPUT_STATE ) );
			XInputGetState( 0, &state );
			XINPUT_VIBRATION vibration;

			if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_A )
			{
				Beep( 5000, 100 );
			}
			if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_B )
			{
				ZeroMemory( &vibration, sizeof( XINPUT_VIBRATION ) );
				vibration.wLeftMotorSpeed = 30000;
				vibration.wRightMotorSpeed = 30000;
				XInputSetState( 0, &vibration );
			}
			if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_Y )
			{
				ZeroMemory( &vibration, sizeof( XINPUT_VIBRATION ) );
				XInputSetState( 0, &vibration );
			}
			float xPad = ( float ) state.Gamepad.sThumbLX / 32768;
			float yPad = ( float ) state.Gamepad.sThumbLY / 32768;

			posx += ( double ) xPad * 15;
			posy += ( double ) yPad * 15 * -1;

			renderer.SetBlendMode( sptAlien->GetBlendMode() );
			sptAlien->Update( screen.ElapsedTime() );
			sptAlien->Render();

			sptAlien->SetPosition( posx, posy );
			// sptAlien->MoveTo( screen.GetMouseX(), screen.GetMouseY(), speed, speed ); // Move to cursor

			if ( screen.KeyPressed( GLFW_KEY_LEFT ) )
			{
				// Rotate to left
				sptAlien->RotateTo( -toAngle, speed );
			}
			else if ( screen.KeyPressed( GLFW_KEY_RIGHT ) )
			{
				// Rotate to right
				sptAlien->RotateTo( toAngle, speed );
				// sptAlien->SetAngle( currDeg );
			}

			// DEBUG
			screen.SetTitle( String::FromInt( sptAlien->GetAngle() ) );
		}
		
		/*
		// PRÁCTICA_7
		if ( BASIC )
		{
			if ( ( int32 ) textPos.x + textWidth / 2 - fontMonospaced->GetWidth() / 2 >= screen.GetWidth() || 
				( int32 ) textPos.x - textWidth / 2 - fontMonospaced->GetWidth() <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedX *= -1;
			}
			if ( ( int32 ) textPos.y + fontMonospaced->GetHeight() / 2 >= screen.GetHeight() || 
				( int32 ) textPos.y - fontMonospaced->GetHeight() / 2 <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedY *= -1;
			}

			textPos.x += textSpeedX * screen.ElapsedTime();
			textPos.y += textSpeedY * screen.ElapsedTime();

			double x = ( double ) ( textPos.x - text.Length() / 2.00 * fontMonospaced->GetWidth() ); // Text centered
			renderer.DrawText( fontMonospaced, text, x, ( double ) textPos.y );
		}
		else
		{
			if ( ( int32 ) textPos.x + textWidth / 2 - fontArial->GetWidth() / 2 >= screen.GetWidth() || 
				( int32 ) textPos.x - textWidth / 2 - fontArial->GetWidth() <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedX *= -1;
			}
			if ( ( int32 ) textPos.y + fontArial->GetHeight() / 2 >= screen.GetHeight() || 
				( int32 ) textPos.y - fontArial->GetHeight() / 2 <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedY *= -1;
			}

			textPos.x += textSpeedX * screen.ElapsedTime();
			textPos.y += textSpeedY * screen.ElapsedTime();

			double x = ( double ) ( textPos.x - text.Length() / 2.00 * fontArial->GetWidth() ); // Text centered
			renderer.DrawText( fontArial, text, x, ( double ) textPos.y );
		}
		*/

		// Refrescamos la pantalla
		screen.Refresh();
	}

	return 0;
}