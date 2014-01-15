#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"


// Práctica de Interfaces

void CreateGUI();
void MouseButtonCallback( int button, int action );
void MousePosCallback( int x, int y );

class Listener : public IEventListener
{
	void onClick( Control* sender )
	{
		std:string name = sender->getName();
		if ( name == "start" )
		{

		}
		else if ( name == "setting" )
		{

		}
		else if ( name == "credits" )
		{

		}
		else if ( name == "exit" )
		{

		}
	}
};

Listener listener;

Font* font;

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// Práctica de Interfaces

	font = resourceManager.LoadFont( "data/fonts/monospaced.png" );

	CreateGUI();
	glfwSetMouseButtonCallback( MouseButtonCallback );
	glfwSetMousePosCallback( MousePosCallback );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		renderer.Clear();

		GUIManager::instance().update();
		GUIManager::instance().render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();
	GUIManager::instance().end();

	return 0;
}

void CreateGUI()
{
	// Init GUI
	GUIManager& guiManager = GUIManager::instance();
	guiManager.init();

	// Create window
	Window* window = new Window();
	window->init( "Main", Vector2( 50, 50 ), "data/gui/Window4.png" );
	window->setEventListener( &listener );
	guiManager.setRootControl( window );

	// Create start game button
	Button* btnStart = new Button();
	btnStart->init( "start", Vector2( window->getSize().x / 2, 100 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Comenzar partida" ); // Add disabled image
	btnStart->setMidHandle();
	btnStart->setScale( font->GetTextWidth( "Comenzar partida " ) / 144.0, btnStart->getScaleY() );
	btnStart->setEventListener( &listener );
	btnStart->setParent( window );

	// Create settings button
	Button* btnSetting = new Button();
	btnSetting->init( "setting", Vector2( window->getSize().x / 2, 150 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Configuracion" ); // Add disabled image
	btnSetting->setMidHandle();
	btnSetting->setScale( font->GetTextWidth( "Configuracion " ) / 144.0, btnSetting->getScaleY() );
	btnSetting->setEventListener( &listener );
	btnSetting->setParent( window );

	// Create credits button
	Button* btnCredits = new Button();
	btnCredits->init( "credits", Vector2( window->getSize().x / 2, 200 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Creditos" ); // Add disabled image
	btnCredits->setMidHandle();
	btnCredits->setScale( font->GetTextWidth( "Creditos " ) / 144.0, btnCredits->getScaleY() );
	btnCredits->setEventListener( &listener );
	btnCredits->setParent( window );

	// Create exit button
	Button* btnExit = new Button();
	btnExit->init( "exit", Vector2( window->getSize().x / 2, 250 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Salir" ); // Add disabled image
	btnExit->setMidHandle();
	btnExit->setScale( font->GetTextWidth( "Salir " ) / 144.0, btnExit->getScaleY() );
	btnExit->setEventListener( &listener );
	btnExit->setParent( window );
}

void MouseButtonCallback( int button, int action )
{
	int x, y;
	glfwGetMousePos( &x, &y );

	if( action == GLFW_PRESS )
		GUIManager::instance().injectInput( MessagePointerButtonDown( button, (float)x, (float)y ) );
	else if( action == GLFW_RELEASE )
		GUIManager::instance().injectInput( MessagePointerButtonUp( button, (float)x, (float)y ) );
}

void MousePosCallback( int x, int y )
{
	GUIManager::instance().injectInput( MessagePointerMove( (float)x, (float)y ) ); 
}