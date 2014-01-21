#include "../include/control.h"
#include <list>
#include <algorithm>
#include "../include/guimanager.h"
#include "../include/math.h"

int Control::s_id = 1000;

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Control::Control()
{
	m_parent					= NULL;
	m_position					= Vector2( 0, 0 );
	m_size						= Vector2( 0, 0 );	
	m_enabled					= true;
	m_visible					= true;
	m_focus						= false;
	m_pointerIsOver				= false;
	m_scalex					= 1.0;
	m_scaley					= 1.0;

	s_id++;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::isPointInside( const Vector2& point ) const
{
	Vector2 pos = getAbsolutePosition() - getHandle() * Vector2( m_scalex, m_scaley );
	if( PointInRect( point.x, point.y, pos.x, pos.y, m_size.x, m_size.y ) )
		return true;

	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Vector2 Control::getAbsolutePosition() const
{
	if( m_parent )
		return m_parent->getAbsolutePosition() + m_position;

	return m_position;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::processUpdate()
{
	update();

	for ( int32 i = 0; i < m_children.Size(); i++ )
	{
		m_children[ i ]->processUpdate();
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::processRender()
{
	render();

	for ( int32 i = 0; i < m_children.Size(); i++ )
	{
		m_children[ i ]->processRender();
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::processDestroy()
{
	// libera sus recursos propios
	destroy();

	// recorre hijos y los destruye
	for ( int32 i = 0; i < m_children.Size(); i++ )
	{
		m_children[ i ]->processDestroy();
	}

	delete this;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::injectInput( const Message& message )
{
	bool messageHandled = false;

	if ( m_enabled && m_visible )
	{
		m_children.Sort( Control::CompareControl ); // Order by depth in DESC way
		// primero vemos si es para algun hijo
		for ( int32 i = m_children.Size() - 1; i >= 0; i-- ) // Checking first controls with lower depth
		{
			Control* control = m_children[ i ];
			if ( control->isEnabled() && control->isVisible() )
				messageHandled = control->injectInput( message );
			if( messageHandled )
				break;
		}

		// si no lo ha procesado ning�n hijo puede ser para este control
		if( !messageHandled )
		{
			switch( message.type )
			{
			case mtPointerMove:
				{
					const MessagePointerMove* messagePointer = static_cast<const MessagePointerMove*>(&message);
					if( isPointInside( Vector2( messagePointer->x, messagePointer->y) ))
					{
						m_pointerIsOver = true;
						onInputEvent( message );
						messageHandled = true;
					}
					else
					{
						m_pointerIsOver = false;
					}
				}
				break;

			case mtPointerButtonDown:
				{
					const MessagePointerButtonDown* messagePointer = static_cast<const MessagePointerButtonDown*>(&message);
					if( isPointInside( Vector2( messagePointer->x, messagePointer->y) ))
					{
						m_pointerIsOver = true;
						onInputEvent( message );
						messageHandled = true;
					}
					else
					{
						m_pointerIsOver = false;
					}
				}
				break;

			case mtPointerButtonUp:
				{
					const MessagePointerButtonUp* messagePointer = static_cast<const MessagePointerButtonUp*>(&message);
					if( isPointInside( Vector2( messagePointer->x, messagePointer->y) ))
					{
						m_pointerIsOver = true;
						onInputEvent( message );
						messageHandled = true;
					}
					else
					{
						m_pointerIsOver = false;
					}
				}
				break;
			}
		}
	}

	return messageHandled;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setParent( Control* parent )
{
	parent->addControl( this );
	m_parent = parent;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setEventListener( IEventListener* eventListener )
{ 
	m_eventListeners.push_back( eventListener ); 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
String Control::getName() const
{ 
	return m_name; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setVisible( bool show )
{ 
	m_visible = show; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::isVisible() const
{ 
	return m_visible; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setEnabled( bool enable )
{ 
	m_enabled = enable; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::isEnabled() const
{ 
	return m_enabled; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setPosition( const Vector2& position )
{ 
	m_position = position; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Vector2 Control::getPosition() const
{ 
	return m_position; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setScale( const double scalex, const double scaley )
{
	m_scalex = scalex;
	m_scaley = scaley;

	m_size.x *= scalex;
	m_size.y *= scaley;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
double Control::getScaleX() const 
{
	return m_scalex;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
double Control::getScaleY() const 
{
	return m_scaley;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Vector2 Control::getSize() const
{ 
	return m_size;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setFocus( bool focus )
{ 
	m_focus = focus; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::hasFocus() const
{ 
	return m_focus; 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::setDepth( int32 depth )
{
	m_depth = depth;
}

int32 Control::getDepth() const
{
	return m_depth;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::addControl( Control* control )
{ 
	m_children.Add( control ); 
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Control::removeControl( Control* control )
{
	m_children.Remove( control );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Control* Control::findControlByName( const String& name )
{
	if( m_name == name )
		return this;

	for ( int32 i = 0; i < m_children.Size(); i++ )
	{
		Control* foundControl = m_children[ i ]->findControlByName( name );
		if( foundControl )
			return foundControl;
	}

	return NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Control::CompareControl( Control*& first, Control*& second )
{
	return first->getDepth() >= second->getDepth();
}