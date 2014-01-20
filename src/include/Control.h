#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <vector>
#include "Vector2.h"
#include "IEventListener.h"
#include <list>
#include "types.h"
#include "string.h"


using namespace std;

class Control
{
	friend class GUIManager;

public:

	Control();
	virtual ~Control(){};

	// A implementar en clases derivadas
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onInputEvent( const Message& message ) = 0;
	virtual void setHandle( int32 handlex, int32 handley ) = 0;
    virtual void setMidHandle() = 0;
	virtual Vector2 getHandle() const = 0;
	virtual void destroy() = 0;

	void setEventListener( IEventListener* eventListener );

	String getName() const;
	virtual Vector2 getAbsolutePosition() const;

	void setVisible( bool show );
	bool isVisible() const;

	void setEnabled( bool enable );
	bool isEnabled() const;

	void setPosition( const Vector2& position );
	Vector2 getPosition() const;

	void setScale( const double scalex, const double scaley );
	double getScaleX() const;
	double getScaleY() const;

	Vector2 getSize() const;

	void setFocus( bool focus );
	bool hasFocus() const;

	void setParent( Control* parent );

	void setDepth( int32 depth );
	int32 getDepth() const;

	bool isPointInside( const Vector2& point ) const;


protected:
	void processUpdate();
	void processRender();
	void processDestroy();
	bool injectInput( const Message& message );

	void addControl( Control* control );
	void removeControl( Control* control );
	Control* findControlByName( const String& name );

	static bool CompareControl( Control*& first, Control*& second );

	// Variables
	String												m_name;
	Vector2												m_position;
	Vector2												m_size;
	bool												m_enabled;
	bool												m_visible;
	bool												m_focus;
	bool												m_pointerIsOver;
	Array<Control*>										m_children; // FIXME: Cambiar tipo a array
	Control*											m_parent;
	list<IEventListener*>								m_eventListeners;
	double												m_scalex, m_scaley;
	int32												m_depth;

	static int											s_id;
};

// Macro para facilitar la llamada a los listeners
#define NOTIFY_LISTENERS( callback ) \
{ \
	list<IEventListener*>::const_iterator it = m_eventListeners.begin(); \
	while( it != m_eventListeners.end() ) \
{ \
	IEventListener *listener = *it; \
	listener->callback; \
	it++; \
} \
}

#endif // _CONTROL_H_