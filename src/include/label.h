#ifndef UGINE_LABEL_H
#define UGINE_LABEL_H

#include "string.h"
#include "Vector2.h"

class Font;

class Label
{
public:
	Label( Font* font, const String& text, const Vector2& position ) : font( font ), text( text ), position( position ) {};

	virtual void Render() const;

	virtual void SetText( const String& text ) { this->text = text; }
	virtual void SetPosition( const Vector2& position ) { this->position = position; }
	virtual void SetX( const float x ) { position.x = x; }
	virtual void SetY( const float y ) { position.y = y; }

private:
	Font* font;
	String text;
	Vector2 position;
};

#endif