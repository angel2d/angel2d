
#ifndef __SOUND_DEVICE_H__
#define __SOUND_DEVICE_H__

#include <map>
#include <vector>
#include <assert.h>

#include "callback.h"

#include "fmod.hpp"
#include "fmod_errors.h"

/* ----------------------------------------------------------------------------

TODO: 
	Add 3D support.
	Cache off a map of filename (base) to SampleID.
	Add Flag support.
	Add next phase of functionality based on feedback and what FMOD has available.
		Some ideas are to support the FMOD Designer files, reverb, etc.

NOTES:
	PlaySound can be told to reuse SoundChannels by adding FMOD_CHANNEL_REUSE
		If FMOD_CHANNEL_REUSE is used, this can contain a previously used channel handle and FMOD will re-use it to play a sound on. 

 
-----------------------------------------------------------------------------*/

void ERRCHECK(FMOD_RESULT result);

#define FMOD_CHECKED( call ) \
{ \
	FMOD_RESULT result = call; \
	ERRCHECK(result); \
} 

#define theSound SoundDevice::GetInstance()

typedef void* SOUND_HANDLE;
typedef void* SAMPLE_HANDLE;

class GameManager;

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

	void SetSoundCallback(GameManager* instance, void (GameManager::*function)(SOUND_HANDLE param))
	{
		soundCallback.SetCallback(instance, function);
	}

	void Update();	//!! Must be called once (and only once) per frame. !!
	void Shutdown();
	
private:
	static FMOD_RESULT F_CALLBACK FMOD_SoundCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, int command, unsigned int commanddata1, unsigned int commanddata2);
	static SoundDevice* s_soundDevice;
	
	SoundDevice() : _system(NULL)
	{
		assert(_system == NULL);
		Initialize();
	}
	
	void Initialize();

	TGenericCallback<GameManager, SOUND_HANDLE> soundCallback;

	FMOD::System*				_system;	
	std::vector<FMOD::Sound*>	_samples;
};

#endif //__SOUND_DEVICE_H__