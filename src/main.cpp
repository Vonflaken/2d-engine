#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	const double degps = 30.00;
	double currDeg = 0.00;

	double scaleps = 2.00;
	double currScale = 1.00;
	const double maxScale = 5.00;
	const double minScale = 0.50;

	bool checkpot = IsPOT( ( double ) 128 );
	bool checknpot = IsPOT( ( double ) 100 );

	// TAREA: Cargar la imagen "data/ball.png"
	Image *imgBall = ResourceManager::Instance().LoadImage( "data/soccer_npot.png", 1, 1 );

	// TAREA: Centrar la imagen
	imgBall->SetMidHandle();

	while ( Screen::Instance().IsOpened() /* TAREA: Salida con ESC */ ) {

		if ( glfwGetKey( GLFW_KEY_ESC ) )
		{
			Screen::Instance().Close();
		}

		// TAREA: Actualizar ángulo y escala de la imagen
		currDeg += degps * Screen::Instance().ElapsedTime();
		currScale += scaleps * Screen::Instance().ElapsedTime();
		if ( currScale >= maxScale )
		{
			scaleps *= -1;
		}
		else if ( currScale <= minScale )
		{
			scaleps *= -1;
		}
		// currScale = PingPong( currScale, maxScale );
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		// TAREA: Limpiar pantalla y dibujar la imagen
		Renderer::Instance().Clear();

		glBindTexture( GL_TEXTURE_2D, imgBall->GetTexId() );
		Renderer::Instance().DrawImage( imgBall, Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 0, imgBall->GetWidth() * currScale, 
			imgBall->GetHeight() * currScale, currDeg );

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	ResourceManager::Instance().FreeResources();

	return 0;
}