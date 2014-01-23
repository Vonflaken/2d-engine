#ifndef UGINE_DRAGABLECONTROL_H
#define UGINE_DRAGABLECONTROL_H

#include "control.h"


class Image;

class DragableControl : public Control
{
public:
	DragableControl();

	virtual void onInputEvent( const Message& message );

	void setDragable( bool dragable );
	void setEnabledAxes( bool x, bool y );

protected:
	bool	m_dragging;

private:
	bool	m_dragable;
	bool	m_enabledX, m_enabledY;
};

#endif