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

	void setBounds( const double x, const double y, const double width, const double height );

protected:
	bool	m_dragging;

private:
	bool	m_dragable;
	bool	m_enabledX, m_enabledY;
	double	m_boundx, m_boundy, m_boundw, m_boundh;
};

#endif