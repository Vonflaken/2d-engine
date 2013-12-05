#include "../include/font.h"
#include "../include/renderer.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>

Font::Font( const String & fileName ) : Image( fileName, 16, 16 )
{
	unsigned char * buffer;

	int32 width = 0, height = 0;
	int32 colorComp = GetColorComp(), reqColorComp = GetColorComp();
	uint32 row = 0, col = 0;

	buffer = stbi_load( GetFilename().ToCString(), ( int * ) &width, ( int * ) &height, ( int * ) &colorComp, reqColorComp );

	for ( uint32 frame = 0; frame < GetNumFrames(); frame++ )
	{
		row = frame / GetHFrames();
		col = frame % GetVFrames();
		Glyph glyph( Vector2D( ( float ) col * GetWidth(), ( float ) row * GetHeight() ), 
			Vector2D( ( float ) ( 1 + col ) * GetWidth(), ( float ) ( 1 + row ) * GetHeight() ) );
		
		for ( uint32 y = row * GetHeight(); y < ( row + 1 ) * GetHeight(); y++ )
		{
			for ( uint32 x = col * GetWidth(); x < ( col + 1 ) * GetWidth(); x++ )
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
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

	free( buffer );
	buffer = NULL;
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
		textWidth += ( uint16 ) glyphs[ ( unsigned char ) text[ i ] ].bottomRight.x - ( uint16 ) glyphs[ ( unsigned char ) text[ i ] ].topLeft.x;
	}

	return textWidth;
}

uint32 Font::GetTextHeight( const String & text ) const
{
	uint32 textHeight = 0, otherHeight = 0;

	for ( int32 i = 0; i < text.Length(); i++ )
	{
		otherHeight = ( uint32 ) glyphs[ ( unsigned char ) text[ i ] ].topLeft.y - ( uint32 ) glyphs[ ( unsigned char ) text[ i ] ].bottomRight.y;
		if ( textHeight < otherHeight )
		{
			textHeight = otherHeight;
		}
	}
	
	return textHeight;
}

void Font::Render( const String & text, double x, double y ) const
{
	uint32 tmpTextWidth = 0;

	for ( int i = 0; i < text.Length(); i++ )
	{
		Renderer::Instance().DrawImage( this, ( i == 0 ) ? x : x + tmpTextWidth, y, ( unsigned char ) text[ i ] );
		tmpTextWidth += ( uint32 ) glyphs[ ( unsigned char ) text[ i ] ].bottomRight.x - ( uint32 ) glyphs[ ( unsigned char ) text[ i ] ].topLeft.x;
	}
}