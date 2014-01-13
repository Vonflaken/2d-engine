#include "../include/label.h"
#include "../include/renderer.h"

void Label::Render() const
{
	if ( font )
		Renderer::Instance().DrawText( font, text, position.x, position.y );
}