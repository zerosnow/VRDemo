#pragma once

#include "AudioBase.h"

class AudioRecorder : public AudioBase
{
public:
	AudioRecorder();
	~AudioRecorder();

	virtual bool openAudioDevice();
	virtual bool openAudioDevice(SLuint32 sampleRate, SLuint32 channels, SLuint32 bufferFrames);
	virtual void closeAudioDevice();

	int AudioIn(short *buffer, int size);
private:
	// recorder interfaces
	SLObjectItf recorderObject;
	SLRecordItf recorderRecord;
	SLAndroidSimpleBufferQueueItf recorderBufferQueue;

};

