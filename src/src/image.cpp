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

	// Generamos la textura
	if ( buffer ) {
		// TAREA: Generar la textura de OpenGL
		glGenTextures( 1, &gltex );
		glBindTexture( GL_TEXTURE_2D, gltex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

		stbi_image_free( buffer );
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
	glBindTexture( GL_TEXTURE_2D, gltex );
}
