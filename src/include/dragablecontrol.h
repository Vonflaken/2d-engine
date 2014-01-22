#ifndef UGINE_DRAGABLECONTROL_H
#define UGINE_DRAGABLECONTROL_H

#include "control.h"


class Image;

class DragableControl : public Control
{
public:
	DragableControl();

	bool init( Image* dragableSurface, bool dragable = false );

	virtual void onInputEvent( const Message& message );

	void setDragable( bool dragable );

protected:
	bool	m_dragging;

private:
	Image*	m_dragableSurface;
	bool	m_dragable;
};

#endif