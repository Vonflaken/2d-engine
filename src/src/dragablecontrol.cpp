#include "../include/dragablecontrol.h"
#include "../include/screen.h"
#include "../include/image.h"


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
DragableControl::DragableControl()
{
	m_dragable										= false;
	m_dragging										= false;
	m_enabledX										= true;
	m_enabledY										= true;
	m_boundx = m_boundy = m_boundw = m_boundh		= -1.0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
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
					Vector2 pos( m_position );
					// FIXME: Positioning well when extend bounds case
					if ( m_enabledX )
					{
						float mousex = (float)Screen::Instance().GetMouseX();
						if ( m_boundw > 0 )
						{
							if ( mousex > m_boundx + m_boundw )
								pos.x = getAbsolutePosition().x - m_boundx + m_boundw;
							if ( mousex < m_boundx )
								pos.x = getAbsolutePosition().x - m_boundx;
						}
						pos.x = ( getAbsolutePosition().x > pos.x ) ? m_position.x - fabs( getAbsolutePosition().x - pos.x ) : m_position.x + fabs( getAbsolutePosition().x - pos.x );
					}
					if ( m_enabledY )
					{
						float mousey = (float)Screen::Instance().GetMouseY();
						if ( m_boundh > 0 )
						{
							if ( mousey > m_boundy + m_boundh )
								pos.y = getAbsolutePosition().y - m_boundy + m_boundh;
							if ( mousey < m_boundy )
								pos.y = getAbsolutePosition().y - m_boundy;
						}
						pos.y = ( getAbsolutePosition().y > pos.y ) ? m_position.y - fabs( getAbsolutePosition().y - pos.y ) : m_position.y + fabs( getAbsolutePosition().y - pos.y );
					}

					setPosition( pos );
				}
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void DragableControl::setDragable( bool dragable )
{
	m_dragable = dragable;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void DragableControl::setEnabledAxes( bool x, bool y )
{
	m_enabledX = x;
	m_enabledY = y;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void DragableControl::setBounds( const double x, const double y, const double w, const double h )
{
	m_boundx = x;
	m_boundy = y;
	m_boundw = w;
	m_boundy = y;
}