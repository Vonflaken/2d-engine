#include "include/u-gine.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "uGui/GUIManager.h"
#include "UGui/Button.h"
#include "uGui/Window.h"
#include "uGui/IEventListener.h"

void CreateGUI();
void MouseButtonCallback(int button, int action);
void MousePosCallback(int x, int y);


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) 
{
	Screen::Instance().Open( 1024, 768, false );
	CreateGUI();

	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);

	while ( Screen::Instance().IsOpened()  &&  !Screen::Instance().KeyPressed(GLFW_KEY_ESC) ) 
	{
		GUIManager::instance().update();

		Renderer::Instance().Clear(0, 0, 0);
		GUIManager::instance().render();
		Screen::Instance().Refresh();
	}

	GUIManager::instance().end();

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void CreateGUI()
{
	// inicializa GUI
	GUIManager& uiManager = GUIManager::instance();
	uiManager.init();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void MouseButtonCallback(int button, int action)
{
	int x, y;
	glfwGetMousePos( &x, &y );

	if( action == GLFW_PRESS )
		GUIManager::instance().injectInput( MessagePointerButtonDown( button, (float)x, (float)y ) );
	else if( action == GLFW_RELEASE )
		GUIManager::instance().injectInput( MessagePointerButtonUp( button, (float)x, (float)y ) );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void MousePosCallback(int x, int y)
{
	GUIManager::instance().injectInput( MessagePointerMove( (float)x, (float)y ) ); 
}