#ifndef UGINE_LABEL_H
#define UGINE_LABEL_H

#include "control.h"
#include "string.h"
#include "Vector2.h"


class Font;

class Label : public Control
{
public:
	bool init( const String name, Font* font, const String& text, const Vector2& position, const int32 depth = 1 );

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void setHandle( int32 handlex, int32 handley );
    virtual void setMidHandle();
	virtual Vector2 getHandle() const;
	virtual void destroy();

	virtual void SetText( const String& text ) { this->text = text; }

	virtual String& GetText() { return text; }
	virtual Font* GetFont() const { return font; }

private:
	Font* font;
	String text;
};

#endif