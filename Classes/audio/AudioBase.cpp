#include "AudioBase.h"
#include "utils/logutil.h"


AudioBase::AudioBase()
{
	LOGD("AudioBase");
	bufferQueue = new BufferQueue();
}

AudioBase::~AudioBase()
{
	LOGD("~AudioBase");
	delete bufferQueue;
	bufferQueue = nullptr;
}

bool AudioBase::openAudioDevice()
{
	return this->openAudioDevice(DEFAULT_SAMPLERATE, DEFAULT_CHANNELS, DEFAULT_FRAME_SIZE);
}

bool AudioBase::openAudioDevice(int sampleRate, int channels, int bufferFrames)
{
	this->sampleRate = sampleRate;
	this->channels = channels;
	this->bufferFrames = bufferFrames;
	
	SLresult result;
	result = slCreateEngine(&mObject, 0, nullptr, 0, nullptr, nullptr);
	if (result != SL_RESULT_SUCCESS) return false;

	result = (*mObject)->Realize(mObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS) return false;

	result = (*mObject)->GetInterface(mObject, SL_IID_ENGINE, &mEngine);
	if (result != SL_RESULT_SUCCESS) return false;

	return true;
}

void AudioBase::closeAudioDevice()
{
	if (mObject != nullptr) {
		(*mObject)->Destroy(mObject);
		mObject = nullptr;
		mEngine = nullptr;
	}
}

void AudioBase::bqCallBack(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	((BufferQueue *)context)->notifyBuffer();
}

SLuint32 AudioBase::getBufferFrame()
{
	return bufferFrames * channels;
}

void AudioBase::addTimeSize(int size)
{
	time += (double)size / (sampleRate*channels);
	//0时间处理
	if (time < 0)
	{
		time = 0;
	}
}
