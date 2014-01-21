#ifndef UGINE_DRAGABLECONTROL_H
#define UGINE_DRAGABLECONTROL_H

#include "control.h"


class Image;

class DragableControl : public Control
{
public:
	DragableControl();

	bool Init( Image* pivot );

	virtual void onInputEvent( const Message& message );

private:
	Image* m_pivot;
};

#endif