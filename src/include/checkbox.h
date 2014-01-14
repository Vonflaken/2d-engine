#ifndef UGINE_CHECKBOX_H
#define UGINE_CHECKBOX_U

#include "button.h"
#include "string.h"


class Font;

class Checkbox : protected Button
{
public:
	Checkbox( const std::string name, const Vector2& position, const String& uncheckedImage, const String& checkedImage, const String& disabledImage, Font* font, const String& text );

	virtual void Toogle();
	virtual bool GetState() const { return checked; }

private:
	bool checked;
};

#endif