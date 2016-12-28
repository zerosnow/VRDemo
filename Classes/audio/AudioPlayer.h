#pragma once

#include "AudioBase.h"

class AudioPlayer : public AudioBase
{
public:
	AudioPlayer();
	~AudioPlayer();

	virtual bool openAudioDevice();
	virtual bool openAudioDevice(SLuint32 sampleRate, SLuint32 channels, SLuint32 bufferFrames);
	virtual void closeAudioDevice();

	int AudioOut(short *buffer, int size);

private:

	SLObjectItf outputMixObject;

	// buffer queue player interfaces
	SLObjectItf bqPlayerObject;
	SLPlayItf bqPlayerPlay;
	SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
	SLEffectSendItf bqPlayerEffectSend;
};

