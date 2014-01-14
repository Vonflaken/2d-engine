#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const bool GUIPractice = true;

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

	// PRÁCTICA_12
	
	double screenX = 0;
	double screenY = 0;
	bool leftPushed = false;
	bool rightPushed = false;
	bool upPushed = false;
	bool downPushed = false;
	double deltaPosX = 0;
	double deltaPosY = 0;

	IsometricMap* isoMap = resourceManager.LoadIsometricMap( "data/maps/isometric.tmx", 11 );
	IsometricScene* isoScene = new IsometricScene( isoMap );
	IsometricSprite* isoSprite = isoScene->CreateSprite( resourceManager.LoadImage( "data/anims/isoplayer.png", 8, 8 ) );
	isoSprite->SetCollision( Sprite::COLLISION_RECT );
	isoSprite->SetPosition( isoMap->GetTileWidth() * 1.5, isoMap->GetTileHeight() * 1.5 );
	isoScene->GetCamera().FollowSprite( isoSprite );

	// Práctica de Interfaces

	font = resourceManager.LoadFont( "data/fonts/monospaced.png" );

	CreateGUI();
	glfwSetMouseButtonCallback( MouseButtonCallback );
	glfwSetMousePosCallback( MousePosCallback );

	while ( screen.IsOpened() && !screen.KeyPressed( GLFW_KEY_ESC ) )
	{
		renderer.Clear();

		renderer.SetBlendMode( renderer.ALPHA );

		if ( !GUIPractice )
		{
			int8 axeX = screen.GetAxis( "horizontal" );
			int8 axeY = screen.GetAxis( "vertical" );
			if ( glfwGetKey( GLFW_KEY_LEFT ) && !leftPushed )
			{
				leftPushed = true;
				rightPushed = false;
				upPushed = false;
				downPushed = false;
				isoSprite->SetFrameRange( 0, 0 + 4 );
				isoSprite->SetCurrentFrame( 0 );
			}
			if ( glfwGetKey( GLFW_KEY_RIGHT ) && !rightPushed )
			{
				rightPushed = true;
				leftPushed = false;
				upPushed = false;
				downPushed = false;
				isoSprite->SetFrameRange( 40, 40 + 4 );
				isoSprite->SetCurrentFrame( 40 );
			}
			if ( glfwGetKey( GLFW_KEY_UP ) && !upPushed )
			{
				upPushed = true;
				leftPushed = false;
				rightPushed = false;
				downPushed = false;
				isoSprite->SetFrameRange( 24, 24 + 4 );
				isoSprite->SetCurrentFrame( 24 );
			}
			if ( glfwGetKey( GLFW_KEY_DOWN ) && !downPushed )
			{
				downPushed = true;
				leftPushed = false;
				rightPushed = false;
				upPushed = false;
				isoSprite->SetFrameRange( 56, 56 + 4 );
				isoSprite->SetCurrentFrame( 56 );
			}
			if ( axeY == 0 && axeX == 0 )
			{
				leftPushed = false;
				rightPushed = false;
				upPushed = false;
				downPushed = false;
			}
			else
				isoSprite->SetFPS( 25 );

			if ( fabs( deltaPosX - isoSprite->GetX() ) < EPSILON && fabs( deltaPosY - isoSprite->GetY() ) < EPSILON )
				isoSprite->SetFPS( 0 );
			if ( axeX != 0 || axeY != 0 )
				isoSprite->MoveTo( isoSprite->GetX() + axeX * isoMap->GetTileWidth() / 2, isoSprite->GetY() + axeY * isoMap->GetTileHeight() / 2, 75, 75 );
			if ( isoSprite->CollisionSprite() )
			{
				isoSprite->SetFPS( 0 );
				isoSprite->SetX( deltaPosX );
				isoSprite->SetY( deltaPosY );
			}
			deltaPosX = isoSprite->GetX();
			deltaPosY = isoSprite->GetY();

			isoScene->Update( screen.ElapsedTime(), isoMap );
			isoScene->Render();
		}
		else
		{
			GUIManager::instance().update();
			GUIManager::instance().render();
		}

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
	btnStart->init( "start", Vector2( 200, 100 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Comenzar partida" ); // Add disabled image
	btnStart->setEventListener( &listener );
	btnStart->setParent( window );

	// Create settings button
	Button* btnSetting = new Button();
	btnSetting->init( "setting", Vector2( 200, 150 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Configuracion" ); // Add disabled image
	btnSetting->setEventListener( &listener );
	btnSetting->setParent( window );

	// Create credits button
	Button* btnCredits = new Button();
	btnCredits->init( "credits", Vector2( 200, 200 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Creditos" ); // Add disabled image
	btnCredits->setEventListener( &listener );
	btnCredits->setParent( window );

	// Create exit button
	Button* btnExit = new Button();
	btnExit->init( "exit", Vector2( 200, 250 ), "data/gui/Button_Normal.png", "data/gui/Button_Push.png", "", font, "Salir" ); // Add disabled image
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