#include "../include/listener.h"

Listener* listener = 0;

Listener& Listener::Instance()
{
	if ( !listener )
		listener = new Listener();

	return *listener;
}

Listener::Listener()
{

}