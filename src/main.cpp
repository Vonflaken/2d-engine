#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	double dCircleAngle = 0;
	double dCircleXCoord = 0;
	double dCircleYCoord = 0;
	uint16 iScreenWidth = Screen::Instance().GetWidth();
	uint16 iScreenHeight = Screen::Instance().GetHeight();
	String angle = "Angle: ";
	String distance = " Distance: ";

	while ( Screen::Instance().IsOpened() /* TAREA: Salida con ESC */ ) {

		double dSquareSize = 24;
		double dCircleSize = 12;
		double dDistanceFromPointerToCircle = 48;
		double dMouseX = 0;
		double dMouseY = 0;

		if ( glfwGetKey( GLFW_KEY_ESC ) )
		{
			Screen::Instance().Close();
		}

		Renderer::Instance().Clear();
		
		dMouseX = Screen::Instance().GetMouseX();
		dMouseY = Screen::Instance().GetMouseY();

		// TAREA: Calcular coordenadas del círculo
		dCircleXCoord = dMouseX + dDistanceFromPointerToCircle * DegCos( dCircleAngle );
		dCircleYCoord = dMouseY + dDistanceFromPointerToCircle * DegSin( dCircleAngle * -1 ); // Nuestra y está invertida respecto a la operación de seno
		dCircleAngle = WrapValue( ++dCircleAngle, 360 );

		// TAREA: Escribir título de la venta
		Screen::Instance().SetTitle( angle + String::FromInt( ( int ) dCircleAngle ) + distance + 
			String::FromInt( Distance( iScreenWidth / 2 - dSquareSize / 2, iScreenHeight / 2 - dSquareSize / 2, dMouseX - dSquareSize / 2, dMouseY - dSquareSize / 2 ) ) );

		// TAREA: Dibujar primitivas
		Renderer::Instance().SetColor( 255, 0, 0, 0 );
		Renderer::Instance().DrawRect( iScreenWidth / 2 - dSquareSize / 2, iScreenHeight / 2 - dSquareSize / 2, dSquareSize, dSquareSize ); // Cuadrado central
		Renderer::Instance().SetColor( 0, 255, 0, 0 );
		Renderer::Instance().DrawRect( dMouseX - dSquareSize / 2, dMouseY - dSquareSize / 2, dSquareSize, dSquareSize ); // Cuadrado puntero
		Renderer::Instance().SetColor( 0, 0, 255, 0 );
		Renderer::Instance().DrawEllipse( dCircleXCoord, dCircleYCoord, dCircleSize, dCircleSize );

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}