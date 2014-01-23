#include "../include/dragablecontrol.h"
#include "../include/screen.h"
#include "../include/image.h"

DragableControl::DragableControl()
{
	m_dragable				= false;
	m_dragging				= false;
	m_enabledX				= true;
	m_enabledY				= true;
}

void DragableControl::onInputEvent( const Message& message )
{
	if ( m_dragable )
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
					Vector2 pos( getAbsolutePosition() );

					if ( m_enabledX )
						pos.x = (float)Screen::Instance().GetMouseX() - m_size.x / 2.f;
					if ( m_enabledY )
						pos.y = (float)Screen::Instance().GetMouseY() - m_size.y / 3.f;

					setPosition( pos );
				}
		}
	}
}

void DragableControl::setDragable( bool dragable )
{
	m_dragable = dragable;
}

void DragableControl::setEnabledAxes( bool x, bool y )
{
	m_enabledX = x;
	m_enabledY = y;
}