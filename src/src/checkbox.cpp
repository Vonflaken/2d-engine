#include "../include/checkbox.h"

Checkbox::Checkbox( const std::string name, const Vector2& position, const String& uncheckedImage, const String& checkedImage, const String& disabledImage, Font* font, const String& text )
{
	this->init( name, position, uncheckedImage, checkedImage, disabledImage, font, text );
	checked = false;
}

void Checkbox::update()
{
	if( !m_pointerIsOver && !checked )
		m_pushed = false;

	m_label->SetPosition( getAbsolutePosition() - getHandle() * Vector2( m_scalex, m_scaley ) );
}

void Checkbox::Toogle()
{
	checked = !checked;
	m_pushed = checked;
}

void Checkbox::onInputEvent( const Message& message )
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
			Toogle();
			break;
		}
	}
}