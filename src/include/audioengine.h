class AudioEngine
{
public:
	static AudioEngine& Instance();

	void Init();
	void End();

protected:
	AudioEngine( void ) : device( 0 ), context( 0 ) {}
	~AudioEngine( void );

private:
	static AudioEngine* engine;
	void* device;
	void* context;
};