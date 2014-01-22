#include "../include/window.h"
#include "../include/guimanager.h"
#include "../include/renderer.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"

Window::Window()
{
	m_canvas					= NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Window::init( const String name, const Vector2& position, const String& backgroungImage, const int32 depth )
{
	DragableControl::init( ResourceManager::Instance().LoadImage( backgroungImage ) );

	m_name					= name;
	m_position				= position;
	m_canvas				= ResourceManager::Instance().LoadImage( backgroungImage );
	m_size					= Vector2( (float)m_canvas->GetWidth(), (float)m_canvas->GetHeight() );
	m_depth					= depth;

	if ( !m_canvas )
		return false; // Not valid

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Window::init( const String name, const int32 depth )
{
	m_name					= name;
	m_position				= Vector2( 0, 0 );
	m_size					= GUIManager::instance().getScreenSize();
	m_depth					= depth;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::update()
{
	if ( !m_pointerIsOver )
		m_dragging = false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::render()
{
	if( m_canvas && m_visible )
	{
		Vector2 pos = getAbsolutePosition();

		Renderer::Instance().SetBlendMode( Renderer::ALPHA );
		Renderer::Instance().DrawImage( m_canvas, pos.x, pos.y, 0, m_canvas->GetWidth() * m_scalex, m_canvas->GetHeight() * m_scaley );
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::onInputEvent( const Message& message )
{
	if ( m_enabled )
	{
		DragableControl::onInputEvent( message );

		switch( message.type )
		{
			case mtPointerButtonUp:
				NOTIFY_LISTENERS( onClick( this ) );
				break;
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::setHandle( int32 handlex, int32 handley )
{
	if ( m_canvas )
		m_canvas->SetHandle( handlex, handley );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::setMidHandle()
{
	if ( m_canvas )
		m_canvas->SetMidHandle();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Vector2 Window::getHandle() const
{
	if ( m_canvas )
		return Vector2( (float)m_canvas->GetHandleX(), (float)m_canvas->GetHandleY() );

	return Vector2( 0, 0 );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Window::destroy()
{

}