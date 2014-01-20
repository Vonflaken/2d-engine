#include "../include/audioengine.h"
#include "../include/alinclude.h"


AudioEngine* AudioEngine::engine = 0;

AudioEngine& AudioEngine::Instance()
{
	if ( !engine )
	{
		engine = new AudioEngine();
		engine->Init();
	}

	return *engine;
}

void AudioEngine::Init()
{
	device = alcOpenDevice( 0 );
	context = alcCreateContext( (ALCdevice*)device, 0 );
	alcMakeContextCurrent( (ALCcontext*)context );
}

void AudioEngine::End()
{
	alcDestroyContext( (ALCcontext*)context );
	alcCloseDevice( (ALCdevice*)device );
}