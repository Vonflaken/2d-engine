#include "../include/font.h"
#include "../include/renderer.h"
#include "../include/math.h"
#include <math.h>

Font::Font( const String & fileName ) : Image( fileName, 16, 16 ) { }

uint16 Font::GetSize() const
{
	return GetHeight();
}

uint32 Font::GetTextWidth( const String & text ) const
{
	return text.Length() * GetWidth();
}

uint32 Font::GetTextHeight( const String & text ) const
{
	return GetHeight();
}

void Font::Render( const String & text, double x, double y ) const
{
	for ( int i = 0; i < text.Length(); i++ )
	{
		Renderer::Instance().DrawImage( this, ( i == 0 ) ? x : x + GetWidth() * i, y, ( uint16 ) text[ i ] );
	}
}