#include "../include/font.h"
#include "../include/renderer.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>

Font::Font( const String & fileName ) : Image( fileName, 16, 16 )
{
	unsigned char * buffer;

	const uint16 & width = GetWidth();
	const uint16 & height = GetHeight();
	uint8 colorComp = GetColorComp(), reqColorComp = GetColorComp();
	uint32 row = 0, col = 0;

	buffer = stbi_load( GetFilename().ToCString(), ( int * ) &width, ( int * ) &height, ( int * ) &colorComp, reqColorComp );

	for ( uint32 frame = 0; frame < GetNumFrames(); frame++ )
	{
		row = frame / GetHFrames();
		col = frame % GetVFrames();
		Glyph glyph( Vector2D( 0.0, 0.0 ), Vector2D( GetWidth(), GetHeight() ) );
		
		for ( uint32 y = row * height; y < ( row + 1 ) * height; y++ )
		{
			for ( uint32 x = col * width; x < ( col + 1 ) * width; x++ )
			{
				unsigned char & r = buffer[ ( y * width + x ) * 4 ];
				unsigned char & g = buffer[ ( y * width + x ) * 4 + 1 ];
				unsigned char & b = buffer[ ( y * width + x ) * 4 + 2 ];
				unsigned char & a = buffer[ ( y * width + x ) * 4 + 3 ];

				if ( ( uint8 ) r == 0 && ( uint8 ) g == 0 && ( uint8 ) b == 0 && ( uint8 ) a == 255 )
				{
					// Black pixel -> background

					r = g = b = a = 0; // Set transparent
				}
				else if ( ( uint8 ) r == 255 && ( uint8 ) g == 255 && ( uint8 ) b == 0 && ( uint8 ) a == 255 )
				{
					// Yellow pixel -> glyph origin

					glyph.topLeft.x = ( float ) x;
					glyph.topLeft.y = ( float ) y;

					r = g = b = a = 0; // Set transparent
				}
				else if ( ( uint8 ) r == 255 && ( uint8 ) g == 0 && ( uint8 ) b == 0 && ( uint8 ) a == 255 )
				{
					// Red pixel -> glyph end
					
					glyph.bottomRight.x = ( float ) x;
					glyph.bottomRight.y = ( float ) y;

					r = g = b = a = 0; // Set transparent
				}
			}
		}

		glyphs.Add( glyph );
	}

	Bind();
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width * GetHFrames(), height * GetVFrames(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
}

uint16 Font::GetSize() const
{
	return GetHeight();
}

uint32 Font::GetTextWidth( const String & text ) const
{
	uint16 textWidth = 0;

	for ( int32 i = 0; i < text.Length(); i++ )
	{
		textWidth += ( uint16 ) glyphs[ ( uint8 ) text[ i ] ].bottomRight.x - ( uint16 ) glyphs[ ( uint8 ) text[ i ] ].topLeft.x;
	}

	return textWidth;
	// return text.Length() * GetWidth();
}

uint32 Font::GetTextHeight( const String & text ) const
{
	uint16 textHeight = 0, otherHeight;

	for ( int32 i = 0; i < text.Length(); i++ )
	{
		otherHeight = ( uint16 ) glyphs[ ( uint8 ) text[ i ] ].topLeft.y - ( uint16 ) glyphs[ ( uint8 ) text[ i ] ].bottomRight.y;
		if ( textHeight < otherHeight )
		{
			textHeight = otherHeight;
		}
	}
	
	return textHeight;
	// return GetHeight();
}

void Font::Render( const String & text, double x, double y ) const
{
	for ( int i = 0; i < text.Length(); i++ )
	{
		Renderer::Instance().DrawImage( this, ( i == 0 ) ? x : x + GetWidth() * i, y, ( uint16 ) text[ i ] );
	}
}