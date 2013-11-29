#include "../include/inputmanager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	End();
}

bool InputManager::Init()
{
	virtualButtons.insert( LEFT, eInputCode::Key_LeftArrow );
}

void InputManager::End()
{
	virtualButtons.clear();
}

bool InputManager::IsOk()
{

}

void InputManager::Update()
{

}

InputManager * InputManager::Instance()
{
	if ( !instance )
	{
		instance = new InputManager();
		instance->Init();
	}

	return instance;
}