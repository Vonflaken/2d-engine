#include "../include/audiolistener.h"

AudioListener* AudioListener::audiolistener = 0;

AudioListener& AudioListener::Instance()
{
	if ( !audiolistener )
		audiolistener = new AudioListener();

	return *audiolistener;
}

AudioListener::AudioListener()
{

}