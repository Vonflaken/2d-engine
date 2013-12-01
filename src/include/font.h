#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "image.h"

class Font : public Image
{
public:
	Font( const String & fileName );

	virtual uint16 GetSize() const;
	virtual uint32 GetTextWidth( const String & text ) const;
	virtual uint32 GetTextHeight( const String & text ) const;

	virtual void Render( const String & text, double x, double y ) const;
};

#endif