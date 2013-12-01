#include "../include/inputmanager.h"

InputManager * InputManager::instance = NULL;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	End();
}

bool InputManager::Init()
{
	// virtualButtons.insert( LEFT, eInputCode::Key_LeftArrow );

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