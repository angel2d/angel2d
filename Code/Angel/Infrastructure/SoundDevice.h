#pragma once

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

//typedefs so our declarations can look more sensible
typedef void* SOUND_HANDLE;
typedef void* SAMPLE_HANDLE;

//singleton shortcut
#define theSound SoundDevice::GetInstance()

//forward declaration
class GameManager;

///Our (very simple) sound system
/** 
 * Our sound system is pretty much just a light wrapper around FMOD. We don't
 *  expose all of FMOD's functionality, but if you're interested in more advanced
 *  usage, it shouldn't be hard to expand this class. 
 * 
 * For more information on FMOD: http://www.fmod.org/
 * 
 * It uses the singleton pattern; you can't actually declare a new instance
 *  of a SoundDevice. To access sound in your world, use "theSound" to retrieve
 *  the singleton object. "theSound" is defined in both C++ and Python. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 */
class SoundDevice
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theSound". 
	 * 
	 * @return The singleton
	 */
	static SoundDevice& GetInstance();
	
	/**
	 * Loads a sound file from disk and gets it ready to be played by the
	 *  system. Depending on how many sounds you're loading at once and/or how
	 *  large they are, this could cause a hiccup. It's best to call this in
	 *  advance of when you actually want to play the sound. 
	 * 
	 * @param filename The path to the file you want to load
	 * @param isStream Whether or not the sound should stream or get loaded
	 *   all at once
	 * @return The SAMPLE_HANDLE that you should hold on to for when you actually
	 *   want to play the sound. You'll pass this to SoundDevice::PlaySound. 
	 */
	SAMPLE_HANDLE LoadSample(const char* filename, bool isStream);
	
	/**
	 * Plays a sound that has been previously loaded. 
	 * 
	 * @param sample The SAMPLE_HANDLE that you got from the 
	 *   SoundDevice::LoadSample function
	 * @param volume The desired loudness of the sound, as a multiplier of its
	 *   normal volume. (1.0 is maximum volume.)
	 * @param looping Whether you want the sound to repeat when it's done
	 * @param flags Currently unused; this will eventually let you pass in
	 *   flags to the underlying sound system (FMOD)
	 * @return The SOUND_HANDLE that you can use to monitor or affect playback
	 */
	SOUND_HANDLE PlaySound(SAMPLE_HANDLE sample, float volume=1.0f, bool looping=false, int flags=0);
	
	/**
	 * Stops a sound that is currently playing. 
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 */
	void StopSound(SOUND_HANDLE sound);
	
	/**
	 * Pauses a sound that is currently playing. It's playback can be resumed
	 *  from the same point later. 
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param paused If true, the sound will be paused. If false, it will
	 *   be unpaused. 
	 */
	void PauseSound(SOUND_HANDLE sound, bool paused);
	
	/**
	 * Find out whether or not a sound is still playing
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @return True if the sound is still playing, false if it's not
	 */
	bool IsPlaying(SOUND_HANDLE sound);
	
	/**
	 * Find out whether a sound is paused
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @return True if the sound is paused, false if it's playing or stopped
	 */
	bool IsPaused(SOUND_HANDLE sound);
	
	/**
	 * Change the stereo positioning of a sound while it's playing. 
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param newPan The new pan value. Should range from -1.0 (full left) to
	 *   1.0 (full right)
	 */
	void SetPan(SOUND_HANDLE sound, float newPan);
	
	/**
	 * Change the volume of a sound while it's playing
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param newVolume The new volume level. Should range from 0.0 (silent) to
	 *   1.0 (full volume)
	 */
	void SetVolume(SOUND_HANDLE sound, float newVolume);
	
	/**
	 * If you set a callback here, it will be executed whenever a sound finishes
	 *  playing. If you're doing a music-or-sound-intensive game, this can be
	 *  very important to you. 
	 * 
	 * Note that the callback you're passing must be a member function of a 
	 *  GameManager. 
	 * 
	 * @param instance The GameManager instance on which to execute the function
	 * @param void The function to execute, which will be passed the SOUND_HANDLE
	 */
	void SetSoundCallback(GameManager* instance, void (GameManager::*function)(SOUND_HANDLE param))
	{
		soundCallback.SetCallback(instance, function);
	}
	
	/**
	 * Calls the underlying FMOD update function to keep the sound thread
	 *  chugging along appropriately. 
	 * 
	 * <b>NB: Must be called once (and only once) per frame. The World already
	 *  calls this function appropriately, so you should only be calling it if
	 *  you really know what you're doing.</b>
	 */
	void Update();
	
	/**
	 * Releases all sounds (invalidating your leftover SOUND_HANDLE and 
	 *  SAMPLE_HANDLE pointers) and shuts down FMOD. Should really only be
	 *  called at the end of the game, which the World handles for you by
	 *  default. 
	 */
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
