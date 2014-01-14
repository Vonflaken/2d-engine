#include "../include/checkbox.h"

Checkbox::Checkbox( const std::string name, const Vector2& position, const String& uncheckedImage, const String& checkedImage, const String& disabledImage, Font* font, const String& text )
{
	this->init( name, position, uncheckedImage, checkedImage, disabledImage, font, text );
	checked = false;
}

void Checkbox::Toogle()
{
	checked = !checked;
	m_pushed = checked;
}