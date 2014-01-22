#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "dragablecontrol.h"
#include "image.h"
#include "Vector2.h"

class Window : public DragableControl
{
public:
	Window();

	bool init( const String name, const int32 depth = 1 );
	bool init( const String name, const Vector2& position, const String& backgroungImage, const int32 depth = 1 );

	void update();
	void render();
	void onInputEvent( const Message& message );
	void setHandle( int32 handlex, int32 handley );
	void setMidHandle();
	Vector2 getHandle() const;
	void destroy();

protected:

	// SDL
	Image*								m_canvas;
};


#endif // _WINDOW_H_