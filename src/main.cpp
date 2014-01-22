#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"


// Práctica de Interfaces

void CreateMenu();
void CreateStart();
void CreateSetting();
void CreateCredits();
void MouseButtonCallback( int button, int action );
void MousePosCallback( int x, int y );

void RequestExit();

class Listener : public IEventListener
{
	void onClick( Control* sender )
	{
		String name = sender->getName();
		if ( name == "start" )
		{
			CreateStart();
		}
		else if ( name == "setting" )
		{
			CreateSetting();
		}
		else if ( name == "credits" )
		{
			CreateCredits();
		}
		else if ( name == "exit" )
		{
			RequestExit();
		}
		else if ( name == "return" )
		{
			CreateMenu();
		}
		else if ( name == "accept" )
		{
			exit( 0 );
		}
		else if ( name == "cancel" )
		{
			CreateMenu();
		}
	}
};

Listener listener;

Font* font;
enum eScene
{
	MENU,
	START,
	SETTING,
	CREDITS
};
eScene renderScene = eScene::MENU;

int main(int argc, char* argv[])
{
	Screen & screen = Screen::Instance();
	const Renderer & renderer = Renderer::Instance();
	ResourceManager & resourceManager = ResourceManager::Instance();

	screen.Open(800, 600, false);

	// Práctica_1 de Programación de Audio

	AudioEngine::Instance().Init();
	AudioBuffer* audiobuffer = new AudioBuffer( "data/sounds/music.wav" );
	AudioSource* audiosource = 0;
	if ( audiobuffer->IsValid() )
		audiosource = new AudioSource( audiobuffer );
	if ( audiosource )
		audiosource->Play();

	float shift = 1.f;
	float soundShiftStep = 0.075;
	float pitch = 1.f;
	float stepPitch = 0.075;

	// Práctica de Interfaces

	font = resourceManager.LoadFont( "data/fonts/monospaced.png" );

	CreateMenu();
	glfwSetMouseButtonCallback( MouseButtonCallback );
	glfwSetMousePosCallback( MousePosCallback );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_BACKSPACE ) )
	{
		renderer.Clear();

		// -----------------------------------

		if ( screen.KeyPressed( GLFW_KEY_RIGHT ) )
		{
			// Right
			shift += soundShiftStep;
		}
		if ( screen.KeyPressed( GLFW_KEY_LEFT ) )
		{
			// Left
			shift -= soundShiftStep;
		}
		if ( screen.KeyPressed( GLFW_KEY_UP ) )
		{
			// Up
			pitch += stepPitch;
		}
		if ( screen.KeyPressed( GLFW_KEY_DOWN ) )
		{
			// Down
			pitch -= stepPitch;
		}

		audiosource->SetPitch( pitch );
		audiosource->SetPosition( shift, 0, 0 );

		// -----------------------------------

		/*
		if ( renderScene == eScene::START )
		{
			if ( screen.KeyPressed( GLFW_KEY_ESC ) )
			{
				// Return to menu
				CreateMenu();
			}
		}
		else if ( renderScene == eScene::SETTING )
		{
			if ( screen.KeyPressed( GLFW_KEY_ESC ) )
			{
				// Return to menu
				CreateMenu();
			}
		}

		GUIManager::instance().update();
		GUIManager::instance().render();
		*/
		// Refrescamos la pantalla
		screen.Refresh();
	}

	// Liberamos recursos
	resourceManager.FreeResources();
	GUIManager::instance().end();
	AudioEngine::Instance().End();

	return 0;
}

void CreateMenu()
{
	renderScene = eScene::MENU;

	// Init GUI
	GUIManager& guiManager = GUIManager::instance();
	guiManager.init();

	// Create window
	Window* window = new Window();
	window->init( "main", Vector2( 50, 50 ), "data/gui/Window4.png" );
	window->setEventListener( &listener );
	window->setDragable( true );
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

void CreateStart()
{
	renderScene = eScene::START;
	GUIManager::instance().init();
}

void CreateSetting()
{
	renderScene = eScene::SETTING;

	GUIManager& guiManager = GUIManager::instance();
	guiManager.init();

	Checkbox* cbGore = new Checkbox();
	cbGore->init( "gore", Vector2( 50.f, 50.f ), "data/gui/CheckBox_disabled.png", "data/gui/CheckBox_enabled.png", "", font, "Modo gore" );
	cbGore->setParent( guiManager.getRootControl() );

	Checkbox* cbParticles = new Checkbox();
	cbParticles->init( "particles", Vector2( 50.f, 150.f ), "data/gui/CheckBox_disabled.png", "data/gui/CheckBox_enabled.png", "", font, "Particulas" );
	cbParticles->setParent( guiManager.getRootControl() );

	Checkbox* cbAutoSave = new Checkbox();
	cbAutoSave->init( "autosave", Vector2( 50.f, 250.f ), "data/gui/CheckBox_disabled.png", "data/gui/CheckBox_enabled.png", "", font, "Auto guardado" );
	cbAutoSave->setParent( guiManager.getRootControl() );
}

void CreateCredits()
{
	renderScene = eScene::CREDITS;

	GUIManager& guiManager = GUIManager::instance();
	guiManager.init();

	Label* lbl01 = new Label();
	lbl01->init( "lbl01", font, "Developed by", Vector2( Screen::Instance().GetWidth() / 2.f , 50.f ) );
	lbl01->setPosition( Vector2( lbl01->getPosition().x - lbl01->GetFont()->GetTextWidth( lbl01->GetText() ) / 2.f, lbl01->getPosition().y ) ); // Get centered
	lbl01->setParent( guiManager.getRootControl() );

	Label* lbl02 = new Label();
	lbl02->init( "lbl02", font, "Ignacio Pascual", Vector2( Screen::Instance().GetWidth() / 2.f , 85.f ) );
	lbl02->setPosition( Vector2( lbl02->getPosition().x - lbl02->GetFont()->GetTextWidth( lbl02->GetText() ) / 2.f, lbl02->getPosition().y ) ); // Get centered
	lbl02->setParent( guiManager.getRootControl() );

	Label* lbl03 = new Label();
	lbl03->init( "lbl03", font, "Build in", Vector2( Screen::Instance().GetWidth() / 2.f , 150.f ) );
	lbl03->setPosition( Vector2( lbl03->getPosition().x - lbl03->GetFont()->GetTextWidth( lbl03->GetText() ) / 2.f, lbl03->getPosition().y ) ); // Get centered
	lbl03->setParent( guiManager.getRootControl() );

	Label* lbl04 = new Label();
	lbl04->init( "lbl04", font, "C++", Vector2( Screen::Instance().GetWidth() / 2.f , 185.f ) );
	lbl04->setPosition( Vector2( lbl04->getPosition().x - lbl04->GetFont()->GetTextWidth( lbl04->GetText() ) / 2.f, lbl04->getPosition().y ) ); // Get centered
	lbl04->setParent( guiManager.getRootControl() );

	Button* btnReturn = new Button();
	btnReturn->init( "return", Vector2( Screen::Instance().GetWidth() / 2.f, 400.f ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Volver" );
	btnReturn->setMidHandle();
	btnReturn->setEventListener( &listener );
	btnReturn->setParent( guiManager.getRootControl() );
}

void RequestExit()
{
	Window* popup = new Window();
	popup->init( "popup_exit", Vector2( 0.f, 0.f ), "data/gui/Window4.png", 0 );
	popup->setScale( 0.5, 0.5 );
	popup->setEventListener( &listener );
	popup->setParent( GUIManager::instance().getRootControl() );
	popup->setPosition( Vector2( GUIManager::instance().getRootControl()->getSize().x / 2.f - popup->getSize().x / 2.f, GUIManager::instance().getRootControl()->getSize().y / 2.f - popup->getSize().y / 2.f) );

	Label* lbl01 = new Label();
	lbl01->init( "exit_ask", font, "Desea salir?", Vector2( 10.f, 5.f ) );
	lbl01->setParent( popup );

	Button* btnAccept = new Button();
	btnAccept->init( "accept", Vector2( 0.f, 0.f ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Si", 0 );
	btnAccept->setEventListener( &listener );
	btnAccept->setParent( popup );
	btnAccept->setPosition( Vector2( popup->getSize().x / 2.f - btnAccept->getSize().x / 2.f - 20.f, 90.f ) );

	Button* btnCancel = new Button();
	btnCancel->init( "cancel", Vector2( 0.f, 0.f ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "No", 0 );
	btnCancel->setEventListener( &listener );
	btnCancel->setParent( popup );
	btnCancel->setPosition( Vector2( popup->getSize().x / 2.f + btnCancel->getSize().x / 2.f + 20.f, 90.f ) );

	popup->setVisible( true );
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