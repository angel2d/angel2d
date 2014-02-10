//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../AngelConfig.h"
#include "../Infrastructure/Callback.h"
#include "../Util/StringUtil.h"

#if !ANGEL_DISABLE_FMOD
	#include <map>
	#include <assert.h>

	#include "fmod.hpp"
	#include "fmod_errors.h"
#else
	#if defined(WIN32) || defined(__linux__)
		#include <AL/al.h>
		#include <AL/alc.h>
	#else
		#include <OpenAL/al.h>
		#include <OpenAL/alc.h>
		#define OV_EXCLUDE_STATIC_CALLBACKS 1
	#endif
	#include <vorbis/vorbisfile.h>
#endif

//typedefs so our declarations can look more sensible
#if !ANGEL_DISABLE_FMOD
	typedef void* AngelSoundHandle;
	typedef void* AngelSampleHandle;
#else
	typedef ALuint AngelSoundHandle;
	typedef ALuint AngelSampleHandle;
#endif

//singleton shortcut
#define theSound SoundDevice::GetInstance()

//forward declaration
class GameManager;

///Our (very simple) sound system
/** 
 * Our sound system is pretty much just a light wrapper around FMOD and OpenAL. 
 *  We don't expose all of their functionality, but if you're interested in 
 *  more advanced usage, it shouldn't be hard to expand this class. 
 * 
 * For more information on FMOD: http://www.fmod.org/
 * 
 * For more information on OpenAL: http://connect.creativelabs.com/openal/default.aspx
 * 
 * Note that FMOD requires licensing fees if you want to distribute your game
 *  for money. Because we're focused on prototyping, and FMOD supports a 
 *  wide array of sound formats while producing very high quality audio, it's 
 *  the default sound system in Angel. If it doesn't fit your needs for some 
 *  reason, though, no worries. This same interface can play sound through OpenAL,
 *  but only in the Ogg Vorbis format. 
 * 
 * To switch to OpenAL, set the ANGEL_DISABLE_FMOD flag in AngelConfig.h
 *  to 1. 
 * 
 * This class uses the singleton pattern; you can't actually declare a new instance
 *  of a SoundDevice. To access sound in your world, use "theSound" to retrieve
 *  the singleton object. "theSound" is defined in both C++ and Lua. 
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
	 * @return The AngelSampleHandle that you should hold on to for when you actually
	 *   want to play the sound. You'll pass this to SoundDevice::PlaySound. 
	 */
	AngelSampleHandle LoadSample(const String& filename, bool isStream);
	
	/**
	 * Plays a sound that has been previously loaded. 
	 * 
	 * @param sample The AngelSampleHandle that you got from the 
	 *   SoundDevice::LoadSample function
	 * @param volume The desired loudness of the sound, as a multiplier of its
	 *   normal volume. (1.0 is maximum volume.)
	 * @param looping Whether you want the sound to repeat when it's done
	 * @param flags Currently unused; this will eventually let you pass in
	 *   flags to the underlying sound system (only supported with FMOD)
	 * @return The AngelSoundHandle that you can use to monitor or affect playback
	 */
	AngelSoundHandle PlaySound(AngelSampleHandle sample, float volume=1.0f, bool looping=false, int flags=0);
	
	/**
	 * Stops a sound that is currently playing. 
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 */
	void StopSound(AngelSoundHandle sound);
	
	/**
	 * Pauses a sound that is currently playing. Its playback can be resumed
	 *  from the same point later. 
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param paused If true, the sound will be paused. If false, it will
	 *   be unpaused. 
	 */
	void PauseSound(AngelSoundHandle sound, bool paused);
	
	/**
	 * Find out whether or not a sound is still playing
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @return True if the sound is still playing, false if it's not
	 */
	bool IsPlaying(AngelSoundHandle sound);
	
	/**
	 * Find out whether a sound is paused
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @return True if the sound is paused, false if it's playing or stopped
	 */
	bool IsPaused(AngelSoundHandle sound);
	
	/**
	 * Change the stereo positioning of a sound while it's playing.
	 * 
	 * NB: If you've disabled FMOD (and are thus using the OpenAL backend), \b only
	 *   \b mono \b sounds will pan properly.  
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param newPan The new pan value. Should range from -1.0 (full left) to
	 *   1.0 (full right)
	 */
	void SetPan(AngelSoundHandle sound, float newPan);
	
	/**
	 * Change the volume of a sound while it's playing
	 * 
	 * @param sound The handle to the playing sound, gotten from SoundDevice::PlaySound
	 * @param newVolume The new volume level. Should range from 0.0 (silent) to
	 *   1.0 (full volume)
	 */
	void SetVolume(AngelSoundHandle sound, float newVolume);
	
	/**
	 * If you set a callback here, it will be executed whenever a sound finishes
	 *  playing. If you're doing a music-or-sound-intensive game, this can be
	 *  very important to you. 
	 * 
	 * Note that the callback you're passing must be a member function of a 
	 *  GameManager. 
	 * 
	 * @param instance The GameManager instance on which to execute the function
	 * @param void The function to execute, which will be passed the AngelSoundHandle
	 */
	void SetSoundCallback(GameManager* instance, void (GameManager::*function)(AngelSoundHandle param))
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
	 * Releases all sounds (invalidating your leftover AngelSoundHandle and 
	 *  AngelSampleHandle pointers) and shuts down FMOD if necessary. Should 
	 *  really only be called at the end of the game, which the World handles 
	 *  for you by default. 
	 */
	void Shutdown();
	
private:
	static SoundDevice* s_soundDevice;
	
	SoundDevice() : _system(NULL)
	{
		Initialize();
	}
	
	void Initialize();

	TGenericCallback<GameManager, AngelSoundHandle> soundCallback;
	
	#if !ANGEL_DISABLE_FMOD
		FMOD::System*				_system;	
		std::vector<FMOD::Sound*>	_samples;
		static FMOD_RESULT F_CALLBACK FMOD_SoundCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2);
	#else
		struct StreamingAudio
		{
			ALuint source;
			ALuint buffers[2];
			OggVorbis_File file;
			vorbis_info* vorbisInfo;
			bool looped;
			ALenum format;
		};
		ALCcontext * _system;
		std::map<ALuint, StreamingAudio> _streams;
		std::vector<ALuint> _buffers;
		std::vector<ALuint> _sources;

		bool _isSampleStreamed(AngelSampleHandle sample);
		bool _streamAudio(ALuint buffer, StreamingAudio &sa);
	#endif

};
