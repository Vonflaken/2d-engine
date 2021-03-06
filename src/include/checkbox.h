#ifndef UGINE_CHECKBOX_H
#define UGINE_CHECKBOX_U

#include "button.h"
#include "string.h"


class Font;

class Checkbox : public Button
{
public:
	Checkbox();

	bool init( const String name, const Vector2& position, const String& uncheckedImage, const String& checkedImage, const String& disabledImage, Font* font, const String& text, const int32 depth = 1 );

	virtual void update();
	virtual void Toogle();
	virtual bool GetState() const { return checked; }

private:
	virtual void onInputEvent( const Message& message );

private:
	bool checked;
};

#endif