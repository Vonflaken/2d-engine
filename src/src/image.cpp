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

	// TAREA: Cargar el buffer de la imagen
	buffer = stbi_load( filename.ToCString(), &width, &height, &colorComp, colorComp );
	bool isPOTWidth = IsPOT( ( double ) width );
	bool isPOTHeight = IsPOT( ( double ) height );

	unsigned char *newBuffer;
	if ( !isPOTWidth || !isPOTHeight )
	{
		// Set buffer data on a new resized buffer
		
		int newWidth = width;
		int newHeight = height;
		unsigned const int bufferSize = width * height * 4;

		newBuffer = ( unsigned char * ) malloc( bufferSize );
		memcpy( newBuffer, buffer, bufferSize );
		// Check sizes to change
		if ( !isPOTWidth )
		{
			newWidth = pow( floor( Log2( ( double ) width ) ), 2 );
			// Set U coor to new ratio based on new width
			lastU = ( ( double ) newWidth ) / width;
		}
		if ( !isPOTHeight )
		{
			newHeight = pow( floor( Log2( ( double ) height ) ), 2 );
			// Set V coor to new ratio based on new height
			lastV = ( ( double ) newHeight ) / height;
		}
		
		buffer = NULL; // stbi_image_free( buffer );
	}
	// Generamos la textura
	if ( buffer ) {
		// TAREA: Generar la textura de OpenGL
		// Set POT texture
		glGenTextures( 1, &gltex );
		glBindTexture( GL_TEXTURE_2D, gltex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

		stbi_image_free( buffer );
	}
	else if ( newBuffer )
	{
		// Set POTed texture
		glGenTextures( 1, &gltex );
		glBindTexture( GL_TEXTURE_2D, gltex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newBuffer );

		newBuffer = NULL;
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
	glBindTexture( GL_TEXTURE_2D, gltex );
}
