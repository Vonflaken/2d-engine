#ifndef UGINE_IMAGE_H
#define UGINE_IMAGE_H

#include "string.h"
#include "types.h"
#include "vector2d.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern unsigned char *stbi_load(char const* fileName, int* width, int* height, int* colorComp, int reqColorComp);
	extern void stbi_image_free(void*);
#ifdef __cplusplus
}
#endif

class Image {
public:
    Image(const String& filename, uint16 hframes = 0, uint16 vframes = 0);
	virtual ~Image();

    virtual bool IsValid() const { return gltex != 0; }
    virtual const String& GetFilename() const { return filename; }
    virtual uint32 GetNumFrames() const { return hframes * vframes; }
    virtual uint16 GetHFrames() const { return hframes; }
    virtual uint16 GetVFrames() const { return vframes; }
    virtual uint16 GetWidth() const { return width / hframes; }
    virtual uint16 GetHeight() const { return height / vframes; }
    virtual void SetHandle(int32 handlex, int32 handley) { this->handlex = handlex; this->handley = handley; }
    virtual void SetMidHandle() { SetHandle(GetWidth()/2, GetHeight()/2); }
    virtual int32 GetHandleX() const { return handlex; }
    virtual int32 GetHandleY() const { return handley; }
    virtual void Bind() const;
    virtual double GetLastU() const { return lastU; }
    virtual double GetLastV() const { return lastV; }
	virtual void SetColorComp( uint8 colorComp ) { this->colorComp = colorComp; }
	virtual uint8 GetColorComp() { return colorComp; }
    virtual uint32 GetTexId() const { return gltex; }
private:
	unsigned char *buffer;
    String filename;
    uint16 hframes, vframes;
    int width, height; // Tipo original: uint16
    int32 handlex, handley;
    uint32 gltex;
    double lastU, lastV;
	int colorComp; // Tipo original: uint8

public:
	class Glyph
	{
	public:
		Vector2D topLeft;
		Vector2D bottomRight;

		Glyph() : topLeft( 0.0, 0.0 ), bottomRight( 0.0, 0.0 ) {};
		Glyph( Vector2D & topLeft, Vector2D & bottomRight )
		{
			this->topLeft = topLeft;
			this->bottomRight = bottomRight;
		}
		~Glyph() {};
	};
};

#endif
