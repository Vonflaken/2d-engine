#include "../include/label.h"
#include "../include/renderer.h"


bool Label::init( const String name, Font* font, const String& text, const Vector2& position, const int32 depth )
{
	m_name		= name;
	this->font	= font;
	this->text	= text;
	m_position	= position;
	m_depth		= depth;

	return true;
}

void Label::update()
{

}

void Label::render()
{
	Vector2 pos = getAbsolutePosition();

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