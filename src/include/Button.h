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

	bool init( const String name, const Vector2& position, const String& normalImage, const String& pushImage, const String& disabledImage = "", Font* font = 0, const String& text = "", const int32 depth = 1 );

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void setHandle( int32 handlex, int32 handley );
    virtual void setMidHandle();
	virtual Vector2 getHandle() const;
	virtual void destroy();

	virtual void setText( String& text );

protected:
	Image*								m_normalImage;
	Image*								m_pushImage;
	Image*								m_disabledImage;
	Label*								m_label;
	bool								m_pushed;
};


#endif // _BUTTON_H_