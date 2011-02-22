%module angel
%{
#include "../../Infrastructure/SoundDevice.h"
%}


%nodefaultctor SoundDevice;
class SoundDevice
{
public:
	static SoundDevice& GetInstance();

	AngelSampleHandle LoadSample(const char *filename, bool isStream);
	AngelSoundHandle PlaySound(AngelSampleHandle sample, float volume=1.0f, bool looping=false, int flags=0);

	void StopSound(AngelSoundHandle sound);
	void PauseSound(AngelSoundHandle sound, bool paused);

	bool IsPlaying(AngelSoundHandle sound);
	bool IsPaused(AngelSoundHandle sound);
	void SetPan(AngelSoundHandle sound, float newPan);
	void SetVolume(AngelSoundHandle sound, float newVolume);
};