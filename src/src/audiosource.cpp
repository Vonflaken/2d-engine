#include "../include/audiosource.h"
#include "../include/alinclude.h"

AudioSource::AudioSource( AudioBuffer* buffer )
{
	// Gen source
	alGenSources( 1, &source );
	
	// Set source params
	alSourcei( source, AL_LOOPING, false );
	alSourcef( source, AL_PITCH, 1.f );
	alSourcef( source, AL_GAIN, 1.f );
	alSource3f( source, AL_POSITION, 0, 0, 0 );
	alSource3f( source, AL_VELOCITY, 0, 0, 0 );

	// Set buffer to the source
	alSourcei( source, AL_BUFFER, buffer->GetBuffer() );
}

void AudioSource::SetPitch( float pitch )
{
	alSourcef( source, AL_PITCH, pitch );
}

void AudioSource::SetGain( float gain )
{
	alSourcef( source, AL_GAIN, gain );
}

void AudioSource::SetLooping( bool loop )
{
	alSourcei( source, AL_LOOPING, loop );
}

void AudioSource::SetPosition( float x, float y, float z )
{
	alSource3f( source, AL_POSITION, x, y, z );
}

void AudioSource::SetVelocity( float x, float y, float z )
{
	alSource3f( source, AL_VELOCITY, x, y, z );
}

void AudioSource::Play()
{
	alSourcePlay( source );
}

void AudioSource::Stop()
{
	alSourceStop( source );
}

void AudioSource::Pause()
{
	alSourcePause( source );
}

bool AudioSource::IsPlaying() const
{
	ALint state;

	alGetSourcei( source, AL_SOURCE_STATE, &state );
	switch( state )
	{
		case AL_PLAYING:
			return true;
		case AL_STOPPED:
			return false;
		case AL_PAUSED:
			return false;
	}
}

AudioSource::~AudioSource()
{
	alDeleteSources( 1, &source );
}