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

#include "stdafx.h"
#include "../Infrastructure/SoundDevice.h"

#include <assert.h>

#include "../Infrastructure/Log.h"

#if ANGEL_DISABLE_FMOD
	#include <vorbis/vorbisfile.h>
	#include <cstdio>
	#include <iostream>
#endif

#if !ANGEL_DISABLE_FMOD
	#define ANGEL_SOUND_CHECKED( call ) \
	{ \
		FMOD_RESULT result = call; \
		ERRCHECK(result); \
	} 

	// Helper function for FMOD errors.
	void ERRCHECK(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			sysLog.Printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		}
	}
#else
	#define ANGEL_SOUND_CHECKED( call ) \
	{ \
		call;\
		ERRCHECK(__LINE__);\
	}

	const char * OpenAL_ErrorString(ALenum errCode)
	{
		String retVal;
		switch (errCode)
		{
			case AL_NO_ERROR:
				retVal = "There is no current error.";
				break;
			case AL_INVALID_NAME:
				retVal = "Invalid name parameter.";
				break;
			case AL_INVALID_ENUM:
				retVal = "Invalid parameter.";
				break;
			case AL_INVALID_VALUE:
				retVal = "Invalid enum parameter value.";
				break;
			case AL_INVALID_OPERATION:
				retVal = "Invalid call.";
				break;
			case AL_OUT_OF_MEMORY:
				retVal = "Unable to allocate memory.";
				break;
			default:
				retVal = "Unknown error.";
		}
		return retVal.c_str();
	}

	void ERRCHECK(int lineNumber)
	{
		ALenum errCode = alGetError();
		while (errCode != AL_NO_ERROR)
		{
			sysLog.Printf("OpenAL error! Line %i: %s", lineNumber, OpenAL_ErrorString(errCode));
			errCode = alGetError();
		}
	}

	// 64 KB buffers; consider increasing this if you're having trouble with streaming audio
	//  skipping, or decreasing it if you're running into memory problems (very unlikely)
	#define ANGEL_OPENAL_BUFFER_SIZE 1024 * 64
#endif

/* static */
SoundDevice* SoundDevice::s_soundDevice = NULL;

/* static */
SoundDevice& SoundDevice::GetInstance()
{
	if (s_soundDevice == NULL)
	{
		s_soundDevice = new SoundDevice();
	}

	return *s_soundDevice;
}

#if !ANGEL_DISABLE_FMOD
/* static */
	FMOD_RESULT F_CALLBACK SoundDevice::FMOD_SoundCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2)	{
		FMOD::Channel *soundChannel = (FMOD::Channel *)channel;

		if (theSound.soundCallback.GetInstance() && theSound.soundCallback.GetFunction())
		{
			theSound.soundCallback.Execute( reinterpret_cast<AngelSoundHandle>(soundChannel) );		
		}

		return FMOD_OK;
	}
#endif

void SoundDevice::Initialize()
{
	if (_system != NULL)
	{
		sysLog.Log("ERROR: Sound system already initialized.");
		return;
	}
	
	#if !ANGEL_DISABLE_FMOD
		unsigned int     version;
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS        caps;

		/* Create a System object and initialize. */
		ANGEL_SOUND_CHECKED( FMOD::System_Create(&_system) )
		ANGEL_SOUND_CHECKED( _system->getVersion(&version) )

		if (version < FMOD_VERSION)
		{
			sysLog.Printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n", version, FMOD_VERSION);
			return;
		}

		// On Linux, sometimes autodetection fails.  Let the user override with an environment variable.
		#ifdef __linux__
			if (getenv("FMOD_OUTPUTTYPE"))
			{
				FMOD_OUTPUTTYPE outtype = FMOD_OUTPUTTYPE_AUTODETECT;
				String FMOD_OUTPUTTYPE_VAR = getenv("FMOD_OUTPUTTYPE");
				if (FMOD_OUTPUTTYPE_VAR == "ALSA")
					outtype = FMOD_OUTPUTTYPE_ALSA;
				else if (FMOD_OUTPUTTYPE_VAR == "OSS")
					outtype = FMOD_OUTPUTTYPE_OSS;
				else if (FMOD_OUTPUTTYPE_VAR == "ESD")
					outtype = FMOD_OUTPUTTYPE_ESD;
				else if (FMOD_OUTPUTTYPE_VAR == "NOSOUND")
					outtype = FMOD_OUTPUTTYPE_NOSOUND;
				else
					sysLog.Printf("Error! Unknown FMOD Output Type...falling back to autodetection.\n");
				ANGEL_SOUND_CHECKED( _system->setOutput(outtype) );
			}
		#endif // __linux__

		ANGEL_SOUND_CHECKED( _system->getDriverCaps(0, &caps, 0, &speakermode) )
		/* Set the user selected speaker mode. */
		ANGEL_SOUND_CHECKED( _system->setSpeakerMode(speakermode) )
		
		/* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
		/* You might want to warn the user about this. */
		if (caps & FMOD_CAPS_HARDWARE_EMULATED)				
		{	
			/* At 48khz, the latency between issuing an fmod command and hearing it will now be about 213ms. */
			ANGEL_SOUND_CHECKED( _system->setDSPBufferSize(1024, 10) )	
		}

		/* Replace with whatever channel count and flags you use! */
		FMOD_RESULT result = _system->init(100, FMOD_INIT_NORMAL, 0);	

		/* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)		
		{
			ANGEL_SOUND_CHECKED( _system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO) )
			/* Replace with whatever channel count and flags you use! */
			ANGEL_SOUND_CHECKED( _system->init(100, FMOD_INIT_NORMAL, 0) ) 
		}
	#else
		ALCdevice *device;
		ALCcontext *context;

		device = alcOpenDevice (NULL);
		if (device == NULL)
		{
			return; //AL_FALSE;
		}

		context = alcCreateContext (device, NULL);
		if (context == NULL)
		{
			alcCloseDevice (device);
			return; //AL_FALSE;
		}

		if (!alcMakeContextCurrent (context))
		{
			alcDestroyContext (context);
			alcCloseDevice (device);
			return; //AL_FALSE;
		}

		//initialisationState = ALUTDeviceAndContext;
		_system = context;
		
		ANGEL_SOUND_CHECKED( alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f) )
	#endif // !ANGEL_DISABLE_FMOD
}

void SoundDevice::Shutdown()
{
	#if !ANGEL_DISABLE_FMOD
		// FMOD documentation on shutting down.
		// Call System::release to close the output device and free all memory associated with that object.
		// Channels are stopped, but sounds are not released. You will have to free them first. You do not have to stop channels yourself.
		// You can of course do it if you want, it is just redundant, but releasing sounds is good programming practice anyway.
		// You do not have to call System::close if you are releasing the system object. System::release internally calls System::close anyway. 

		std::vector<FMOD::Sound*>::iterator it = _samples.begin();
		while ( it != _samples.end() )
		{
			(*it++)->release();
		}
		_samples.clear();

		// Shutdown FMOD.
		ANGEL_SOUND_CHECKED( _system->release() )
		
		// Give back the memory for the SoundDevice.
		delete s_soundDevice;
	#else
		std::vector<ALuint>::iterator it = _sources.begin();
		while (it != _sources.end())
		{
			alDeleteSources(1, &(*it));
			it++;
		}
		it = _buffers.begin();
		while (it != _buffers.end())
		{
			alDeleteBuffers(1, &(*it));
			it++;
		}

		ALCdevice *device;

		if (!alcMakeContextCurrent (NULL))
		{
			return; //AL_FALSE;
		}

		device = alcGetContextsDevice (_system);
		alcDestroyContext (_system);
		if (alcGetError (device) != ALC_NO_ERROR)
		{
			return; //AL_FALSE;
		}

		if (!alcCloseDevice (device))
		{
			return; //AL_FALSE;
		}
	#endif // !ANGEL_DISABLE_FMOD
}

AngelSampleHandle SoundDevice::LoadSample(const String& filename, bool isStream)
{
	#if !ANGEL_DISABLE_FMOD
		int flags = FMOD_DEFAULT;
		if (isStream )
			flags |= FMOD_CREATESTREAM;

		FMOD::Sound* newSample;
		ANGEL_SOUND_CHECKED( _system->createSound(filename.c_str(), flags, 0, &newSample) ) 

		// We don't try and stop duplicates.  If they want to have multiples of the 
		//  same stream going at once, they have to have unique samples loaded for each.
		_samples.push_back(newSample);

		return newSample;
	#else
		int endian = 0;
		int bitStream;
		long bytes;
		char initialBuffer[ANGEL_OPENAL_BUFFER_SIZE];
		std::vector<char> fullBuffer;
		FILE *f;
		ALenum format;
		ALsizei freq;
		ALuint bufferID;

		vorbis_info *pInfo;
		OggVorbis_File oggFile;

		f = fopen(filename.c_str(), "rb");

		if (f == NULL)
		{
			sysLog.Printf("ERROR: Could not find file named \"%s\"", filename.c_str());
			return 0;
		}

		ov_open(f, &oggFile, NULL, 0);
		pInfo = ov_info(&oggFile, -1);
		
		if (pInfo == NULL)
		{
			sysLog.Printf("ERROR: \"%s\" is not a valid Ogg Vorbis file.", filename.c_str());
			return 0;
		}
	
		if (pInfo->channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}

		freq = pInfo->rate;

		if (!isStream) {
			do
			{
				bytes = ov_read(&oggFile, initialBuffer, ANGEL_OPENAL_BUFFER_SIZE, endian, 2, 1, &bitStream);
				fullBuffer.insert(fullBuffer.end(), initialBuffer, initialBuffer + bytes);
			} while (bytes > 0);

			ov_clear(&oggFile);

			ANGEL_SOUND_CHECKED( alGenBuffers(1, &bufferID) )
			ANGEL_SOUND_CHECKED( alBufferData(bufferID, format, &fullBuffer[0], static_cast<ALsizei> (fullBuffer.size()), freq) )
			
			_buffers.push_back(bufferID);

			return bufferID;
		}
		else
		{
			StreamingAudio sa;
			ANGEL_SOUND_CHECKED( alGenBuffers(2, sa.buffers) )
			sa.source = 0;
			sa.file = oggFile;
			sa.format = format;
			sa.vorbisInfo = pInfo;

			_streams[sa.buffers[0]] = sa;
			
			_buffers.push_back(sa.buffers[0]);
			_buffers.push_back(sa.buffers[1]);

			return sa.buffers[0];
		}
	#endif // !ANGEL_DISABLE_FMOD
}

#if ANGEL_DISABLE_FMOD
	bool SoundDevice::_isSampleStreamed(AngelSampleHandle sample)
	{
		std::map<ALuint, StreamingAudio>::iterator it = _streams.find(sample);
		if (_streams.end() == it)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool SoundDevice::_streamAudio(ALuint buffer, StreamingAudio &sa)
	{
		// grab datums from the file
		char bufferData[ANGEL_OPENAL_BUFFER_SIZE];
		int size = 0;
		int section;
		int result;

		while (size < ANGEL_OPENAL_BUFFER_SIZE)
		{
			result = ov_read(&sa.file, bufferData + size, ANGEL_OPENAL_BUFFER_SIZE - size, 0, 2, 1, &section);
			
			if (result > 0)
			{
				size += result;
			}
			else
			{
				if (result < 0)
				{
					// error handling
				}
				else // result == 0
				{
					break;
				}
			}
		}

		if (size == 0)
		{
			return false;
		}
		else
		{
			ANGEL_SOUND_CHECKED( alBufferData(buffer, sa.format, bufferData, size, sa.vorbisInfo->rate) )
			return true;
		}
	}
#endif // ANGEL_DISABLE_FMOD

AngelSoundHandle SoundDevice::PlaySound(AngelSampleHandle sample, float volume, bool looping, int flags)
{
	#if !ANGEL_DISABLE_FMOD
		if (sample == NULL)
		{
			sysLog.Log("ERROR: Invalid AngelSampleHandle.");
			return NULL;
		}
	
		if (flags)
			sysLog.Log("WARNING: PlaySound doesn't use the passed in flags yet.");

		// Start paused, tweak setting and unpause.
		FMOD::Channel* FMOD_Channel;
		FMOD::Sound* FMOD_Sound = reinterpret_cast<FMOD::Sound*>(sample);
		ANGEL_SOUND_CHECKED( _system->playSound(FMOD_CHANNEL_FREE, FMOD_Sound, true/*paused*/, &FMOD_Channel) )

		// Volume.
		ANGEL_SOUND_CHECKED( FMOD_Channel->setVolume(volume) )
		
		// Looping.
		int modeFlags = 0;
		if (looping)
			modeFlags |= FMOD_LOOP_NORMAL;
		else
			modeFlags |= FMOD_LOOP_OFF;
		ANGEL_SOUND_CHECKED( FMOD_Channel->setMode(modeFlags) )
		
		// Unpause.
		ANGEL_SOUND_CHECKED( FMOD_Channel->setPaused(false) )
		
		FMOD_Channel->setCallback(&SoundDevice::FMOD_SoundCallback);

		return FMOD_Channel;
	#else
		ALuint sourceID;
		ANGEL_SOUND_CHECKED(alGenSources(1, &sourceID))
		alSource3f(sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcef(sourceID, AL_GAIN, volume);

		_sources.push_back(sourceID);

		if (!_isSampleStreamed(sample)) 
		{
			// Not streamed; just do the simple play
			alSourcei(sourceID, AL_BUFFER, sample);
			alSourcei(sourceID, AL_LOOPING, looping);
			ANGEL_SOUND_CHECKED( alSourcePlay(sourceID) )
		}
		else
		{
			if (!_streamAudio(_streams[sample].buffers[0], _streams[sample]))
			{
				return 0;
			}

			if (!_streamAudio(_streams[sample].buffers[1], _streams[sample]))
			{
				return 0;
			}

			_streams[sample].source = sourceID;
			_streams[sample].looped = looping;
			ANGEL_SOUND_CHECKED( alSourceQueueBuffers(sourceID, 2, _streams[sample].buffers) )
			ANGEL_SOUND_CHECKED( alSourcePlay(sourceID) )
		}

		return sourceID;
	#endif // !ANGEL_DISABLE_FMOD
}

void SoundDevice::Update()
{
	#if !ANGEL_DISABLE_FMOD
		ANGEL_SOUND_CHECKED( _system->update() )
	#else
		std::map<ALuint, StreamingAudio>::iterator it = _streams.begin();
		while (it != _streams.end())
		{
			if (it->second.source == 0)
			{
				continue;
			}

			int processed;
			bool active = true;
			alGetSourcei(it->second.source, AL_BUFFERS_PROCESSED, &processed);

			while (processed--)
			{
				ALuint buffer;

				ANGEL_SOUND_CHECKED( alSourceUnqueueBuffers(it->second.source, 1, &buffer) )

				active = _streamAudio(buffer, it->second);

				ANGEL_SOUND_CHECKED( alSourceQueueBuffers(it->second.source, 1, &buffer) )

				// check to make sure we're still playing...
				//   (if we didn't get update calls for a while [like if the player was
				//    moving the window or something], we may have run out our existing 
				//    buffers and gotten stopped by OpenAL)
				if (!IsPlaying(it->second.source))
				{
					alSourcePlay(it->second.source);
					break;
				}
			}

			if (!active)
			{
				// done streaming -- repeat?
				if (it->second.looped)
				{
					// NOTE: Somewhere in here is the secret to avoiding popping
					//   in loops. If someone can suss it out, they would have
					//   glory and songs in their name. -- SJML

					//ANGEL_SOUND_CHECKED( alSourceUnqueueBuffers(it->second.source, 2, it->second.buffers) )
					ov_raw_seek(&it->second.file, 0);
					//_streamAudio(it->second.buffers[0], it->second);
					//_streamAudio(it->second.buffers[1], it->second);
					//ANGEL_SOUND_CHECKED( alSourceQueueBuffers(it->second.source, 2, it->second.buffers) )					
				}
				else
				{
					if (theSound.soundCallback.GetInstance() && theSound.soundCallback.GetFunction())
					{
						theSound.soundCallback.Execute(it->second.source);
					}
					_streams.erase(it->second.source);
				}
			}

			it++;
		}
	#endif
}

void SoundDevice::StopSound(AngelSoundHandle sound)
{
	if (!sound)
		return;
	
	#if !ANGEL_DISABLE_FMOD
		FMOD::Channel* FMOD_Channel = reinterpret_cast<FMOD::Channel*>(sound);
		ANGEL_SOUND_CHECKED( FMOD_Channel->stop() )
	#else
		ANGEL_SOUND_CHECKED( alSourceStop(sound) )
	#endif
}

void SoundDevice::PauseSound(AngelSoundHandle sound, bool paused)
{
	if (!sound)
		return;

	#if !ANGEL_DISABLE_FMOD
		ANGEL_SOUND_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setPaused(paused) )
	#else
		if (paused)
		{
			ANGEL_SOUND_CHECKED( alSourcePause(sound) )
		}
		else
		{
			ANGEL_SOUND_CHECKED( alSourcePlay(sound) )
		}	
	#endif
}

bool SoundDevice::IsPlaying(AngelSoundHandle sound)
{
	if (!sound)
		return false;

	#if !ANGEL_DISABLE_FMOD
		bool playing = false;
		ANGEL_SOUND_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->isPlaying(&playing) )

		return (playing);
	#else
		ALint state;
		alGetSourcei(sound, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	#endif
}

bool SoundDevice::IsPaused(AngelSoundHandle sound)
{
	if (!sound)
		return false;
	
	#if !ANGEL_DISABLE_FMOD
		bool paused = false;
		ANGEL_SOUND_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->getPaused(&paused) )

		return (paused);
	#else
		ALint state;
		alGetSourcei(sound, AL_SOURCE_STATE, &state);
		return (state == AL_PAUSED);
	#endif
}

void SoundDevice::SetPan(AngelSoundHandle sound, float newPan)
{
	if (!sound)
		return;

	#if !ANGEL_DISABLE_FMOD
		ANGEL_SOUND_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setPan(newPan) )
	#else
		ALfloat pos[] = {newPan, 0.0f, 0.0f};
		ANGEL_SOUND_CHECKED( alSourcefv(sound, AL_POSITION, pos) )
	#endif
}

void SoundDevice::SetVolume(AngelSoundHandle sound, float newVolume)
{
	if (!sound)
		return;

	#if !ANGEL_DISABLE_FMOD
		ANGEL_SOUND_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setVolume(newVolume) )
	#else
		ANGEL_SOUND_CHECKED( alSourcef(sound, AL_GAIN, newVolume) )
	#endif
}
