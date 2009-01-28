
#include "../CollisionResponse/PlaySoundCollisionResponse.h"

#include "../Physics/PhysicsEventActor.h"
#include "../Infrastructure/SoundDevice.h"
#include "../Util/StringUtil.h"

void PlaySoundCollisionResponse::Execute()
{
	theSound.PlaySound(_sample,1.0f,false,0);
}

CollisionResponse* PlaySoundCollisionResponse::FactoryMethod( const StringList& input )
{
	if( input.size() > 0 )
	{
		SAMPLE_HANDLE sample = theSound.LoadSample(input[0].c_str(), false /*not streaming*/);
		if (sample)
		{
			PlaySoundCollisionResponse* pColResponse = new PlaySoundCollisionResponse();
			pColResponse->_volume = 1.0f;
			pColResponse->_sample = sample;

			if( input.size() > 1 )
			{
				pColResponse->_volume = StringToFloat(input[1] );
			}

			return pColResponse;
		}
	}

	return NULL;
}
