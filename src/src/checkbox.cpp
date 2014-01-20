#include "../include/checkbox.h"

Checkbox::Checkbox()
{
	checked = false;
}

bool Checkbox::init( const String name, const Vector2& position, const String& uncheckedImage, const String& checkedImage, const String& disabledImage, Font* font, const String& text, const int32 depth )
{
	Button::init( name, position, uncheckedImage, checkedImage, disabledImage, font, text, depth );

	if ( m_label )
		m_label->setPosition( Vector2( m_normalImage->GetWidth() + 20.f, m_normalImage->GetHeight() / 2.f - m_label->GetFont()->GetSize() / 2.f ) ); // FIXME: Remove magic numbers: add vars offsetx and offsety

	return true;
}

void Checkbox::update()
{
	if( !m_pointerIsOver && !checked )
		m_pushed = false;
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