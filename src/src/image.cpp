#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

// TAREA: Declarar funciones de stb_image.c

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;
	colorComp = 4;
	references = 0;

	// TAREA: Cargar el buffer de la imagen
	buffer = stbi_load( filename.ToCString(), &width, &height, &colorComp, colorComp );

	bool isPOTWidth = IsPOT( ( double ) width );
	bool isPOTHeight = IsPOT( ( double ) height );
	int newWidth = width;
	int newHeight = height;

	unsigned char *newBuffer;
	if ( !isPOTWidth || !isPOTHeight )
	{
		// Set buffer data on a new resized buffer

		// Check sizes to change
		if ( !isPOTWidth )
		{
			newWidth = pow( 2, ceil( Log2( ( double ) width ) ) );
			// Set U coor to new ratio based on new width
			lastU = ( ( double ) width ) / newWidth;
		}
		if ( !isPOTHeight )
		{
			newHeight = pow( 2, ceil( Log2( ( double ) height ) ) );
			// Set V coor to new ratio based on new height
			lastV = ( ( double ) height ) / newHeight;
		}

		unsigned const int bufferSize = newWidth * newHeight * 4;
		newBuffer = ( unsigned char * ) malloc( bufferSize );
		memset( newBuffer, 0, bufferSize );

		for ( uint16 x = 0; x < height; x++ )
		{
			for ( uint16 y = 0; y < width; y++ )
			{
				for ( uint8 i = 0; i < colorComp; i++ )
				{
					newBuffer[ ( x * newWidth + y ) * 4 + i ] = buffer[ ( x * width + y ) * 4 + i ];
				}
			}
		}
		stbi_image_free( buffer );
		buffer = NULL;
	}
	// Generamos la textura
	// FIXME: Rehacer sin el condicional -> aplicando el mismo buffer
	if ( buffer ) {
		// TAREA: Generar la textura de OpenGL
		// Set POT texture
		glGenTextures( 1, &gltex );
		glBindTexture( GL_TEXTURE_2D, gltex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

		free( buffer );
		buffer = NULL;
	}
	else if ( newBuffer )
	{
		// Set POTed texture
		glGenTextures( 1, &gltex );
		glBindTexture( GL_TEXTURE_2D, gltex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newBuffer );

		free( newBuffer );
		newBuffer = NULL;
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const
{
	glBindTexture( GL_TEXTURE_2D, gltex );
}