#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define BASIC false

int main(int argc, char* argv[])
{
	Screen &screen = Screen::Instance();
	const Renderer &renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// ------------- BASIC ------------- //

	Font * fontMonospaced = resourceManager.LoadFont( "data/monospaced.png" );
	String text = "Hola, mundo";
	int32 textWidth = text.Length() * fontMonospaced->GetWidth();
	float textSpeedX = Random( 128.0, 255.0 );
	float textSpeedY = Random( 128.0, 255.0 );
	Vector2D textPos( ( float ) screen.GetWidth() / 2, ( float ) screen.GetHeight() / 2 ); 

	// ------------- ADVANCED ------------- //

	Font * fontArial = resourceManager.LoadFont( "data/arial16.png" );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{	
		renderer.Clear();
		
		if ( BASIC )
		{
			if ( ( int32 ) textPos.x + textWidth / 2 - fontMonospaced->GetWidth() / 2 >= screen.GetWidth() || 
				( int32 ) textPos.x - textWidth / 2 - fontMonospaced->GetWidth() <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedX *= -1; // FIXME: Desplazarlo un pequeño espacio hacia el lado contrario para evitar bug de stuck
			}
			if ( ( int32 ) textPos.y + fontMonospaced->GetHeight() / 2 >= screen.GetHeight() || 
				( int32 ) textPos.y - fontMonospaced->GetHeight() / 2 <= 0 )
			{
				renderer.SetColor( ( uint8 ) Random( 0.0, 255.0 ), ( uint8 ) Random( 0.0, 255.0 ), 
					( uint8 ) Random( 0.0, 255.0 ), 255 );
				textSpeedY *= -1; // FIXME: Desplazarlo un pequeño espacio hacia el lado contrario para evitar bug de stuck
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

		// Refrescamos la pantalla
		screen.Refresh();
	}

	return 0;
}