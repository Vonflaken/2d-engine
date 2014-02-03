#ifndef UGINE_SLIDER_H
#define UGINE_SLIDER_H

#include "dragablecontrol.h"


class Font;
class Image;

class Slider : public Control
{
	class Pivot;

public:
	Slider();

	bool init( const String name, const Vector2& position, const String& barImage, const String& pivotImage, const double min, const double max, const double step, const String& disabledPivotImage = "", const int32 depth = 1 );

	virtual void update();
	virtual void render();
	virtual void onInputEvent( const Message& message );
	virtual void setHandle( int32 handlex, int32 handley );
    virtual void setMidHandle();
	virtual Vector2 getHandle() const;
	virtual void destroy();

	double getValue() const;
	void setValue( double value );

	void setRange( double min, double max );

	void setStep( double step );

	void setVertical();
	void setHorizontal();

private:
	Image* m_barImage;
	Pivot* m_pivot;
	double m_min, m_max;
	double m_step;

	class Pivot : public DragableControl
	{
	public:
		Pivot();

		bool init( const String name, const Vector2& position, const String& pivotImage, double &min, double &max, double &step, const String& disabledPivotImage = "" );

		virtual void update();
		virtual void render();
		virtual void onInputEvent( const Message& message );
		virtual void setHandle( int32 handlex, int32 handley );
		virtual void setMidHandle();
		virtual Vector2 getHandle() const;
		virtual void destroy();

		double getValue() const;

	private:
		double m_value;
		double m_min, m_max;
		double m_step;
		Image* m_pivotImage;
		Image* m_disablePivotImage;
	};
};

#endif