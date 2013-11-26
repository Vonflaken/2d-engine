#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[])
{
	Screen &screen = Screen::Instance();
	const Renderer &renderer = Renderer::Instance();

	screen.Open(800, 600, false);

	const double stripeWidth = screen.GetWidth() / 3;
	const double midX = screen.GetWidth() / 2;
	const double midY = screen.GetHeight() / 2;
	const double circleSize = 35.00;
	const double circleGapX = circleSize / 2;
	const double circleGapY = circleGapX * 2;
	const double fromFrame = 100.00;

	while ( Screen::Instance().IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) ) {

		// TAREA: Pintar franjas de pantalla
		renderer.SetBlendMode( renderer.SOLID );
		// Left stripe
		renderer.SetColor( 0, 0, 0, 255 );
		renderer.DrawRect( 0, 0, stripeWidth, screen.GetHeight() );
		// Center stripe
		renderer.SetColor( 255, 255, 255, 255 );
		renderer.DrawRect( screen.GetWidth() / 3, 0, stripeWidth, screen.GetHeight() );
		// Right stripe
		renderer.SetColor( 0, 0, 0, 255 );
		renderer.DrawRect( screen.GetWidth() - stripeWidth, 0, stripeWidth, screen.GetHeight() );

		// TAREA: Pintar c�rculos en modo SOLID, ALPHA, MULTIPLICATIVE Y ADDITIVE
		// SOLID
		renderer.SetBlendMode( renderer.SOLID );
		renderer.SetColor( 255, 0, 0, 255 );
		renderer.DrawEllipse( midX, fromFrame, circleSize, circleSize );										// Red
		renderer.SetColor( 0, 255, 0, 255 );
		renderer.DrawEllipse( midX - circleGapX, fromFrame + circleGapY, circleSize, circleSize );				// Green
		renderer.SetColor( 0, 0, 255, 255 );
		renderer.DrawEllipse( midX + circleGapX, fromFrame + circleGapY, circleSize, circleSize );				// Blue
		// ALPHA
		renderer.SetBlendMode( renderer.ALPHA );
		renderer.SetColor( 255, 0, 0, 128 );
		renderer.DrawEllipse( stripeWidth / 2, midY - circleGapY, circleSize, circleSize );						// Red
		renderer.SetColor( 0, 255, 0, 128 );
		renderer.DrawEllipse( stripeWidth / 2 - circleGapX, midY, circleSize, circleSize );						// Green
		renderer.SetColor( 0, 0, 255, 128 );
		renderer.DrawEllipse( stripeWidth / 2 + circleGapX, midY, circleSize, circleSize );						// Blue
		// MULTIPLICATIVE
		renderer.SetBlendMode( renderer.MULTIPLICATIVE );
		renderer.SetColor( 255, 0, 0, 255 );
		renderer.DrawEllipse( midX, midY + fromFrame, circleSize, circleSize );								// Red
		renderer.SetColor( 0, 255, 0, 255 );
		renderer.DrawEllipse( midX - circleGapX, midY + fromFrame + circleGapY, circleSize, circleSize );	// Green
		renderer.SetColor( 0, 0, 255, 255 );
		renderer.DrawEllipse( midX + circleGapX, midY + fromFrame + circleGapY, circleSize, circleSize );	// Blue
		// ADDITIVE
		renderer.SetBlendMode( renderer.ADDITIVE );
		renderer.SetColor( 255, 0, 0, 255 );
		renderer.DrawEllipse( stripeWidth * 2.5, midY - circleGapY, circleSize, circleSize );				// Red
		renderer.SetColor( 0, 255, 0, 255 );
		renderer.DrawEllipse( stripeWidth * 2.5 - circleGapX, midY, circleSize, circleSize );				// Green
		renderer.SetColor( 0, 0, 255, 255 );
		renderer.DrawEllipse( stripeWidth * 2.5 + circleGapX, midY, circleSize, circleSize );				// Blue

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}

	return 0;
}