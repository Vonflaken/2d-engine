#include "../include/inputmanager.h"
#include "../include/glinclude.h"

InputManager * InputManager::instance = NULL;

InputManager::InputManager()
{
	mouse = false;
	keyboard = false;
	pad = false;
}

InputManager::~InputManager()
{
	End();
}

bool InputManager::Init()
{
	return true;
}

void InputManager::End()
{
	virtualButtons.clear();
}

bool InputManager::IsOk()
{
	return true;
}

void InputManager::Update()
{
	for ( std::map< const String, uint8 >::iterator it = virtualButtons.begin(); it != virtualButtons.end(); it++ )
	{
		int state = glfwGetKey( it->second );
	}
}

void InputManager::CreateVirtualButton( const String & key, uint8 value )
{
	virtualButtons.insert( std::pair< const String, uint8 >( key, value ) );
}

InputManager & InputManager::Instance()
{
	if ( !instance )
	{
		instance = new InputManager();
		instance->Init();
	}

	return * instance;
}