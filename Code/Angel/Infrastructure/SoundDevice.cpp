//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
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
#include <assert.h>

#include "../Infrastructure/SoundDevice.h"
#include "../Infrastructure/Log.h"

// Helper function for FMOD errors.
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		sysLog.Printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		assert(0);
	}
}

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

/* static */
FMOD_RESULT F_CALLBACK SoundDevice::FMOD_SoundCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, int command, unsigned int commanddata1, unsigned int commanddata2)
{
	FMOD::Channel *soundChannel = (FMOD::Channel *)channel;

	//rb - Here's how we can get at user data if we need it.
	//void* userData;
	//FMOD_CHECKED( soundChannel->getUserData(&userData) )
	//assert(userData);

	if (theSound.soundCallback.GetInstance() && theSound.soundCallback.GetFunction())
	{
		theSound.soundCallback.Execute( reinterpret_cast<SOUND_HANDLE>(soundChannel) );		
	}

	return FMOD_OK;
}

void SoundDevice::Initialize()
{
	unsigned int     version;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS        caps;

	/* Create a System object and initialize. */
	FMOD_CHECKED( FMOD::System_Create(&_system) )
	FMOD_CHECKED( _system->getVersion(&version) )

	if (version < FMOD_VERSION)
	{
		sysLog.Printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n", version, FMOD_VERSION);
		return;
	}

	// On Linux, sometimes autodetection fails.  Let the user override with an environment variable.
	// If no environment variable is provided, default to ALSA.
	#ifdef __linux__
	FMOD_OUTPUTTYPE outtype = FMOD_OUTPUTTYPE_ALSA;
	if (getenv("FMOD_OUTPUTTYPE"))
	{
		String FMOD_OUTPUTTYPE_VAR = getenv("FMOD_OUTPUTTYPE");
		if (FMOD_OUTPUTTYPE_VAR == "ALSA")
			outtype = FMOD_OUTPUTTYPE_ALSA;
		else if (FMOD_OUTPUTTYPE_VAR == "OSS")
			outtype = FMOD_OUTPUTTYPE_OSS;
		else if (FMOD_OUTPUTTYPE_VAR == "ESD")
			outtype = FMOD_OUTPUTTYPE_ESD;
		else if (FMOD_OUTPUTTYPE_VAR == "NOSOUND")
			outtype = FMOD_OUTPUTTYPE_NOSOUND;
		else if (FMOD_OUTPUTTYPE_VAR == "AUTODETECT")
			outtype = FMOD_OUTPUTTYPE_AUTODETECT;
		else
			sysLog.Printf("Error! Unknown FMOD Output Type...defaulting to ALSA.\n");
	}
	FMOD_CHECKED( _system->setOutput(outtype) );
	#endif	

	FMOD_CHECKED( _system->getDriverCaps(0, &caps, 0, 0, &speakermode) )
	/* Set the user selected speaker mode. */
	FMOD_CHECKED( _system->setSpeakerMode(speakermode) )
	
	/* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
	/* You might want to warn the user about this. */
	if (caps & FMOD_CAPS_HARDWARE_EMULATED)				
	{	
		/* At 48khz, the latency between issuing an fmod command and hearing it will now be about 213ms. */
		FMOD_CHECKED( _system->setDSPBufferSize(1024, 10) )	
	}

#if 0 //rb - It's not in their required startup sequence, but might fix some sound issues on some PCs.
	char name[256];
	FMOD_CHECKED( _system->getDriverInfo(0, name, 256, 0) )
	
	/* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
	if (strstr(name, "SigmaTel"))   
	{
		FMOD_CHECKED( _system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMfloat, 0,0, FMOD_DSP_RESAMPLER_LINEAR) )
	}
#endif

	/* Replace with whatever channel count and flags you use! */
	FMOD_RESULT result = _system->init(100, FMOD_INIT_NORMAL, 0);	

	/* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)		
	{
		FMOD_CHECKED( _system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO) )
		/* Replace with whatever channel count and flags you use! */
		FMOD_CHECKED( _system->init(100, FMOD_INIT_NORMAL, 0) ) 
	}
}

void SoundDevice::Shutdown()
{
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
	FMOD_CHECKED( _system->release() )
	
	// Give back the memory for the SoundDevice.
	delete s_soundDevice;
}

SAMPLE_HANDLE SoundDevice::LoadSample(const char *filename, bool isStream)
{
	int flags = FMOD_DEFAULT;
	if (isStream )
		flags |= FMOD_CREATESTREAM;

	FMOD::Sound* newSample;
	FMOD_CHECKED( _system->createSound(filename, flags, 0, &newSample) ) 

	// We don't try and stop duplicates.  If they want to have multiple of the same stream going at once, they have to have 
	// unique samples loaded for each.
	_samples.push_back(newSample);

	return newSample;
}

//rb - TODO - Add flags for Persistent or not?  
//rb - TODO - Add method to load sample and play sound?  
SOUND_HANDLE SoundDevice::PlaySound(SAMPLE_HANDLE sample, float volume, bool looping, int flags)
{
	assert(sample && "Sample is NULL.");
	//rb - TODO - Allow for flags.  Translate from wrapper flags to FMOD flags.
	// Currently, we don't use flags, but this way the interface is intact.
	if (flags)
		sysLog.Log("WARNING: PlaySound doesn't use the passed in flags yet.");

	//int numChannelsActive;
	//_system->getChannelsPlaying(&numChannelsActive);
	//if (numChannelsActive >= 25)
	//	return NULL;

	// Start paused, tweak setting and unpause.
	FMOD::Channel* FMOD_Channel;
	FMOD::Sound* FMOD_Sound = reinterpret_cast<FMOD::Sound*>(sample);
	FMOD_CHECKED( _system->playSound(FMOD_CHANNEL_FREE, FMOD_Sound, true/*paused*/, &FMOD_Channel) )

	// Volume.
	FMOD_CHECKED( FMOD_Channel->setVolume(volume) )
	
	// Looping.
	int modeFlags = 0;
	if (looping)
		modeFlags |= FMOD_LOOP_NORMAL;
	else
		modeFlags |= FMOD_LOOP_OFF;
	FMOD_CHECKED( FMOD_Channel->setMode(modeFlags) )
	
	// Unpause.
	FMOD_CHECKED( FMOD_Channel->setPaused(false) )
	
	//rb - Here's how we can set user data if we need it.
	//FMOD_Channel->setUserData(FMOD_Channel);
	
	//rb - Should we always call the callback?
	FMOD_Channel->setCallback(FMOD_CHANNEL_CALLBACKTYPE_END, &SoundDevice::FMOD_SoundCallback, 0);

	return FMOD_Channel;
}

void SoundDevice::Update()
{
	FMOD_CHECKED( _system->update() )	
}

void SoundDevice::StopSound(SOUND_HANDLE sound)
{
	if (!sound)
		return;

	FMOD::Channel* FMOD_Channel = reinterpret_cast<FMOD::Channel*>(sound);
	FMOD_CHECKED( FMOD_Channel->stop() )
}

void SoundDevice::PauseSound(SOUND_HANDLE sound, bool paused)
{
	if (!sound)
		return;

	FMOD_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setPaused(paused) )
}

bool SoundDevice::IsPlaying(SOUND_HANDLE sound)
{
	if (!sound)
		return false;

	bool playing = false;
	FMOD_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->isPlaying(&playing) )

	return (playing);
}

bool SoundDevice::IsPaused(SOUND_HANDLE sound)
{
	if (!sound)
		return false;

	bool paused = false;
	FMOD_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->getPaused(&paused) )

	return (paused);
}

void SoundDevice::SetPan(SOUND_HANDLE sound, float newPan)
{
	if (!sound)
		return;

	FMOD_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setPan(newPan) )
}

void SoundDevice::SetVolume(SOUND_HANDLE sound, float newVolume)
{
	if (!sound)
		return;

	FMOD_CHECKED( reinterpret_cast<FMOD::Channel*>(sound)->setVolume(newVolume) )
}
