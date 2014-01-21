#include "../include/audiobuffer.h"
#include "../include/file.h"
#include "../include/alinclude.h"


AudioBuffer::AudioBuffer( const String& filename )
{
	alBuffer = 0;

	File wavfile( filename, 0 );

	char validator[ 5 ];
	validator[ 4 ] = 0;
	// Get useful and validable data from WAV file
	wavfile.ReadBytes( validator, 4 );
	if ( String( validator ) != "RIFF" )
		return;
	int32 chunksize					= wavfile.ReadInt();
	wavfile.ReadBytes( validator, 4 );
	if ( String( validator ) != "WAVE" )
		return;
	wavfile.ReadBytes( validator, 4 );
	if ( String( validator ) != "fmt " )
		return;
	int32 subchunksize				= wavfile.ReadInt();
	int16 audioformat				= wavfile.ReadInt16();
	int16 channels					= wavfile.ReadInt16();
	int32 samplerate				= wavfile.ReadInt();
	int32 byterate					= wavfile.ReadInt();
	int16 blockalign				= wavfile.ReadInt16();
	int16 bitspersample				= wavfile.ReadInt16();
	
	if ( audioformat != 16 && audioformat != 1 )
	{
		// ExtraParams exists
		int16 extraparamssize			= wavfile.ReadInt16();
		wavfile.Seek( wavfile.Pos() + extraparamssize );
	}
	
	wavfile.ReadBytes( validator, 4 );
	// Search "data" block
	while ( String( validator ) != "data" )
	{
		if ( wavfile.ReadBytes( validator, 4 ) < 4 )
			return;
	}

	int32 datasize = wavfile.ReadInt();
	char* databuffer = (char*)malloc( datasize );
	wavfile.ReadBytes( databuffer, datasize );

	alGenBuffers( 1, &alBuffer );
	alBufferData( alBuffer, channels != 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, databuffer, datasize, samplerate );

	delete databuffer;
}

AudioBuffer::~AudioBuffer()
{
	// delete databuffer;
	alDeleteBuffers( 1, &alBuffer );
}