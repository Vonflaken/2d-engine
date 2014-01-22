#include "../include/dragablecontrol.h"
#include "../include/screen.h"

DragableControl::DragableControl()
{
	m_dragable				= false;
	m_dragging				= false;
	m_dragableSurface		= 0;
}

bool DragableControl::init( Image* dragableSurface, bool dragable )
{
	m_dragableSurface		= dragableSurface;
	m_dragable				= dragable;

	return true;
}

void DragableControl::onInputEvent( const Message& message )
{
	if ( m_dragable && m_dragableSurface )
	{
		switch( message.type )
		{
			case mtPointerButtonDown:
				m_dragging = true;
				break;
			case mtPointerButtonUp:
				m_dragging = false;
				break;
			case mtPointerMove:
				if ( m_dragging )
				{
					float newPosX, newPosY;
					newPosX = Screen::Instance().GetMouseX() - getAbsolutePosition().x;
					newPosY = Screen::Instance().GetMouseY() - getAbsolutePosition().y;
					setPosition( Vector2( Screen::Instance().GetMouseX() - 300.f, Screen::Instance().GetMouseY() - 30.f  ) );
				}
		}
	}
}

void DragableControl::setDragable( bool dragable )
{
	m_dragable = dragable;
}