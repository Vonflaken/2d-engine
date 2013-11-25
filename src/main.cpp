#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(800, 600, false);

	while ( Screen::Instance().IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) ) {

		// TAREA: Pintar franjas de pantalla

		// TAREA: Pintar círculos en modo SOLID, ALPHA, MULTIPLICATIVE Y ADDITIVE
		
		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}

	return 0;
}