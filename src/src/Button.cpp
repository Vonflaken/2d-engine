#include "../include/button.h"
#include "../include/guimanager.h"
#include "../include/Renderer.h"
#include "../include/Image.h"
#include "../include/resourcemanager.h"
#include "../include/label.h"


//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
	m_pushed = false;
	m_enabled = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
bool Button::init( const std::string name, const Vector2& position, const String& normalImage, const String& pushImage, const String& disabledImage, Font* font, const String& text )
{
	m_name				= name;
	m_position			= position;
	m_normalImage		= ResourceManager::Instance().LoadImage( normalImage );
	m_pushImage			= ResourceManager::Instance().LoadImage( pushImage );
	m_disabledImage		= ResourceManager::Instance().LoadImage( disabledImage );
	m_size				= Vector2( ( float )m_normalImage->GetWidth(), ( float )m_normalImage->GetHeight() );
	m_label				= new Label( font, text, position );

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::update()
{
	if( !m_pointerIsOver )
		m_pushed = false;
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
			if( m_pushed )
			{
				Renderer::Instance().DrawImage( m_pushImage, pos.x, pos.y );
			}
			else if( !m_pushed )
			{
				Renderer::Instance().DrawImage( m_normalImage, pos.x, pos.y );
			}
		}
		else
		{
			if ( m_disabledImage )
				Renderer::Instance().DrawImage( m_disabledImage, pos.x, pos.y );
			else
				Renderer::Instance().DrawImage( m_normalImage, pos.x, pos.y ); // m_disabledImage fallback
		}
	}

	// Render text
	m_label->Render();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------------------------------------
void Button::onInputEvent( const Message& message )
{
	if ( m_enabled )
	{
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
void Button::destroy()
{
	if( m_normalImage )
	{
		delete m_normalImage;
		m_normalImage = NULL;
	}
	if( m_pushImage )
	{
		delete m_pushImage;
		m_pushImage = NULL;
	}
	if ( m_disabledImage )
	{
		delete m_disabledImage;
		m_disabledImage = NULL;
	}

	delete m_label;
	m_label = NULL;
}