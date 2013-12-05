#include "../include/inputmanager.h"
#include "../include/glinclude.h"

InputManager * InputManager::instance = NULL;

InputManager::~InputManager()
{
	End();
}

bool InputManager::Init()
{
	mouse = false;
	keyboard = false;
	pad = false;

	up = false;
	down = false;
	right = false;
	left = false;

	if ( !instance )
	{
		return false;
	}

	return true;
}

void InputManager::End()
{
	virtualButtons.clear();
}

bool InputManager::IsOk()
{
	if ( !instance )
	{
		return false;
	}

	return true;
}

void InputManager::Update()
{
	for ( std::map< eAction, int32 >::iterator it = virtualButtons.begin(); it != virtualButtons.end(); it++ )
	{
		switch ( it->first )
		{
		case UP:
			up = glfwGetKey( it->second );
			break;
		case RIGHT:
			right = glfwGetKey( it->second );
			break;
		case DOWN:
			down = glfwGetKey( it->second );
			break;
		case LEFT:
			left = glfwGetKey( it->second );
			break;
		case JUMP:
			jump = glfwGetKey( it->second );
			break;
		default:
			break;
		}
	}
}

void InputManager::CreateVirtualButton( eAction key, int32 value )
{
	virtualButtons.insert( std::pair< eAction, int32 >( key, value ) );
}

bool InputManager::GetActionState( eAction action ) const
{
	switch ( action )
		{
		case UP:
			return up;
		case RIGHT:
			return right;
		case DOWN:
			return down;
		case LEFT:
			return left;
		case JUMP:
			return jump;
		default:
			break;
	}
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