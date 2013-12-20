#define UGINE_COLLISIONPIXELDATA_H
#ifndef UGINE_COLLISIONPIXELDATA_H

#include "string.h"

class CollisionPixelData
{
public:
	CollisionPixelData( const String& filename );
	virtual ~CollisionPixelData();

	virtual bool IsValid() const { if ( data ) return true; return false; };
	virtual const String& GetFilename() const { return filename; }
	virtual uint16 GetWidth() const { return width; }
	virtual uint16 GetHeight() const { return height; }
	virtual bool GetData( uint32 x, uint32 y ) const { return data[ ( x + y * width ) * 4 + 3 ] } ;

private:
	String filename;
	uint16 width, height;
	bool* data;
};

#endif