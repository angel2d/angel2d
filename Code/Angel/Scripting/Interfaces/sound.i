%module angel
%{
#include "../../Infrastructure/SoundDevice.h"
%}

typedef void* SOUND_HANDLE;
typedef void* SAMPLE_HANDLE;

%nodefaultctor SoundDevice;
class SoundDevice
{
public:
	static SoundDevice& GetInstance();

	SAMPLE_HANDLE LoadSample(const char *filename, bool isStream);
	SOUND_HANDLE PlaySound(SAMPLE_HANDLE sample, float volume=1.0f, bool looping=false, int flags=0);

	void StopSound(SOUND_HANDLE sound);
	void PauseSound(SOUND_HANDLE sound, bool paused);

	bool IsPlaying(SOUND_HANDLE sound);
	bool IsPaused(SOUND_HANDLE sound);
	void SetPan(SOUND_HANDLE sound, float newPan);
	void SetVolume(SOUND_HANDLE sound, float newVolume);
};