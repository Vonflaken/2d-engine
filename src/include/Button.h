#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "control.h"
#include "Vector2.h"
#include "label.h"
#include "font.h"


class Image;

class Button : public Control
{
public:
	Button();

	bool init( const std::string name, const Vector2& position, const String& normalImage, const String& pushImage, const String& disabledImage = "", Font* font = 0, const String& text = "" );

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void destroy();

	virtual void setText( String& text ) { m_label->SetText( text ); }

protected:
	Image*								m_normalImage;
	Image*								m_pushImage;
	Image*								m_disabledImage;
	Label*								m_label;
	bool								m_pushed;

public:
	bool								m_enabled;
};


#endif // _BUTTON_H_