#include "../include/button.h"
#include "../include/guimanager.h"
#include "../include/renderer.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/label.h"


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
	m_pushed = false;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Button::init( const String name, const Vector2& position, const String& normalImage, const String& pushImage, const String& disabledImage, Font* font, const String& text, const int32 depth )
{
	m_name				= name;
	m_position			= position;
	m_normalImage		= ResourceManager::Instance().LoadImage( normalImage );
	m_pushImage			= ResourceManager::Instance().LoadImage( pushImage );
	m_disabledImage		= ResourceManager::Instance().LoadImage( disabledImage );
	m_size				= Vector2( (float)m_normalImage->GetWidth(), (float)m_normalImage->GetHeight() );
	m_depth				= depth;
	m_label				= new Label();
	m_label->init( "label of " + name, font, text, Vector2(), depth );
	m_label->setParent( this );

	if ( !m_normalImage || !m_pushImage )
		return false; // Not valid

	if ( !m_disabledImage )
		m_disabledImage = m_normalImage;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::update()
{
	if( !m_pointerIsOver )
	{
		m_pushed = false;
		m_dragging = false;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::render()
{
	if( m_visible )
	{
		Vector2 pos = getAbsolutePosition();

		Renderer::Instance().SetBlendMode( Renderer::ALPHA );
		if ( m_enabled )
		{
			if ( m_pushed )
				Renderer::Instance().DrawImage( m_pushImage, pos.x, pos.y, 0, m_pushImage->GetWidth() * m_scalex, m_pushImage->GetHeight() * m_scaley );
			else
				Renderer::Instance().DrawImage( m_normalImage, pos.x, pos.y, 0, m_normalImage->GetWidth() * m_scalex, m_normalImage->GetHeight() * m_scaley );
		}
		else
		{
			Renderer::Instance().DrawImage( m_disabledImage, pos.x, pos.y, 0, m_disabledImage->GetWidth() * m_scalex, m_disabledImage->GetHeight() * m_scaley );
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::onInputEvent( const Message& message )
{
	if ( m_enabled )
	{
		DragableControl::onInputEvent( message );

		switch( message.type )
		{
		case mtPointerButtonDown:
			m_pushed = true;
			break;

		case mtPointerButtonUp:
			if( m_pushed )
				NOTIFY_LISTENERS( onClick( this ) );
			m_pushed = false;
			break;
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::setHandle( int32 handlex, int32 handley )
{
	if ( m_normalImage )
		m_normalImage->SetHandle( handlex, handley );
	if ( m_pushImage )
		m_pushImage->SetHandle( handlex, handley );
	if ( m_disabledImage )
		m_disabledImage->SetHandle( handlex, handley );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::setMidHandle()
{
	if ( m_normalImage )
		m_normalImage->SetMidHandle();
	if ( m_pushImage )
		m_pushImage->SetMidHandle();
	if ( m_disabledImage )
		m_disabledImage->SetMidHandle();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Vector2 Button::getHandle() const
{
	if ( m_normalImage )
		return Vector2( (float)m_normalImage->GetHandleX(), (float)m_normalImage->GetHandleY() );

	return Vector2( 0, 0 );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::setText( String& text )
{
	m_label->SetText( text );
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::destroy()
{

}