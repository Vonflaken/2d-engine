#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	// TAREA: Cargar la imagen "data/ball.png"
	Image *imgBall = ResourceManager::Instance().LoadImage( "data/ball.png", 1, 1 );
	// TAREA: Centrar la imagen

	while ( Screen::Instance().IsOpened() /* TAREA: Salida con ESC */ ) {

		if ( glfwGetKey( GLFW_KEY_ESC ) )
		{
			Screen::Instance().Close();
		}

		// TAREA: Actualizar ángulo y escala de la imagen

		// TAREA: Limpiar pantalla y dibujar la imagen
		Renderer::Instance().Clear();

		glBindTexture( GL_TEXTURE_2D, imgBall->GetTexId() );
		Renderer::Instance().DrawImage( imgBall, 50, 50 );

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	ResourceManager::Instance().FreeResources();

	return 0;
}