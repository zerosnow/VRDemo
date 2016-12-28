#pragma once

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "BufferQueue.h"

class AudioBase
{
public:
	AudioBase();
	~AudioBase();

	SLuint32 getBufferFrame();
	virtual bool openAudioDevice();
	virtual bool openAudioDevice(int sampleRate, int channels, int bufferFrames);
	virtual void closeAudioDevice();
protected:
	const SLuint32 DEFAULT_SAMPLERATE = SL_SAMPLINGRATE_44_1;
	const SLuint32 DEFAULT_CHANNELS = 2;
	const SLuint32 DEFAULT_FRAME_SIZE = DEFAULT_SAMPLERATE * 20 / 1000000;

	SLObjectItf mObject;
	SLEngineItf mEngine;

	double time;
	SLuint32 channels;
	SLuint32 sampleRate;
	SLuint32 bufferFrames;

	BufferQueue *bufferQueue;
	static void bqCallBack(SLAndroidSimpleBufferQueueItf bq, void *context);
private:
	
};

