#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	while ( Screen::Instance().IsOpened() ) {
		// TAREA: Pintar primitivas
		Renderer::Instance().Clear( 255, 255, 0 );

		Renderer::Instance().SetColor( 255, 0, 0, 0 );
		Renderer::Instance().DrawRect( 16, 16, 800 - 32, 600 - 32 );
		Renderer::Instance().SetColor( 0, 255, 0, 0 );
		Renderer::Instance().DrawEllipse( 400, 150, 360, 110 );

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}