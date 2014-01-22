#ifndef UGINE_AUDIOLISTENER_H
#define UGINE_AUDIOLISTENER_H

class AudioListener
{
public:
	static AudioListener& Instance();

	void SetPosition( float x, float y, float z );
	void SetVelocity( float x, float y, float z );
	void SetOrientation( float x, float y, float z );

protected:
	AudioListener();
	~AudioListener() {}

private:
	static AudioListener* audiolistener;
};

#endif