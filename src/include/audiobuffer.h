#include "string.h"


class AudioBuffer
{
public:
	AudioBuffer( const String& filename );
	~AudioBuffer( void );

	bool IsValid() const { return alBuffer != 0; }
	unsigned int GetBuffer() const { return alBuffer; }

private:
	unsigned int alBuffer;
};