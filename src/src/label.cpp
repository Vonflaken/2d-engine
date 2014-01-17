#include "../include/label.h"
#include "../include/renderer.h"


bool Label::init( Font* font, const String& text, const Vector2& position )
{
	this->font = font;
	this->text = text;
	m_position = position;

	return true;
}

void Label::update()
{

}

void Label::render()
{
	Vector2 pos = getAbsolutePosition();
	if ( m_parent )
		pos = getAbsolutePosition() - m_parent->getHandle() * Vector2( m_parent->getScaleX(), m_parent->getScaleY() );
	if ( font )
		Renderer::Instance().DrawText( font, text, pos.x, pos.y );
}

void Label::onInputEvent( const Message& message )
{

}

void Label::setHandle( int32 handlex, int32 handley )
{

}

void Label::setMidHandle()
{

}

Vector2 Label::getHandle() const
{
	return Vector2( 0.f, 0.f );
}

void Label::destroy()
{

}