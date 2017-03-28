#include "AudioRecord.h"
#include "utils/logutil.h"

AudioRecorder::AudioRecorder()
{
	LOGD("AudioRecorder");
}

AudioRecorder::~AudioRecorder()
{
}

int AudioRecorder::AudioIn(short *buffer, int size)
{
	short *inBuffer;
	int i, bufsamps = bufferQueue->bufferSize, index = bufferQueue->currentIndex;
	if (bufsamps == 0) return 0;

	inBuffer = bufferQueue->getBuffer();
	for (i = 0; i < size; i++) {
		if (index >= bufsamps) {
			inBuffer = bufferQueue->waitBuffer(recorderBufferQueue);
			index = 0;
		}
		buffer[i] = inBuffer[index++];
	}
	bufferQueue->currentIndex = index;
	time += (double)size / (sampleRate*channels);
	return i;
}

bool AudioRecorder::openAudioDevice()
{
	return this->openAudioDevice(DEFAULT_SAMPLERATE, DEFAULT_CHANNELS, DEFAULT_FRAME_SIZE);
}

bool AudioRecorder::openAudioDevice(SLuint32 sampleRate, SLuint32 channels, SLuint32 bufferFrames)
{
	if (!AudioBase::openAudioDevice(sampleRate, channels, bufferFrames))
	{
		LOGE("AudioBase::openAudioDevice ERROR");
		return false;
	}


	if (!bufferQueue->init(channels * bufferFrames, channels * bufferFrames))
	{
		LOGE("bufferQueue->init ERROR");
		return false;
	}


	if (channels) {
		SLresult result;

		// configure audio source
		SLDataLocator_IODevice loc_dev = { SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
			SL_DEFAULTDEVICEID_AUDIOINPUT, nullptr };
		SLDataSource audioSrc = { &loc_dev, nullptr };

		// configure audio sink
		SLuint32 channelMask;
		if (channels > 1)
			channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
		else channelMask = SL_SPEAKER_FRONT_CENTER;

		SLDataLocator_AndroidSimpleBufferQueue loc_bq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, channels, sampleRate,
			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
			channelMask, SL_BYTEORDER_LITTLEENDIAN };
		SLDataSink audioSnk = { &loc_bq, &format_pcm };

		// create audio recorder
		// (requires the RECORD_AUDIO permission)
		const SLInterfaceID id[1] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		const SLboolean req[1] = { SL_BOOLEAN_TRUE };
		result = (*mEngine)->CreateAudioRecorder(mEngine, &(recorderObject), &audioSrc,
			&audioSnk, 1, id, req);
		if (SL_RESULT_SUCCESS != result) return false;

		// realize the audio recorder
		result = (*recorderObject)->Realize(recorderObject, SL_BOOLEAN_FALSE);
		if (SL_RESULT_SUCCESS != result) return false;

		// get the record interface
		result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &(recorderRecord));
		if (SL_RESULT_SUCCESS != result) return false;

		// get the buffer queue interface
		result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
			&(recorderBufferQueue));
		if (SL_RESULT_SUCCESS != result) return false;

		// register callback on the buffer queue
		result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, AudioBase::bqCallBack, bufferQueue);
		if (SL_RESULT_SUCCESS != result) return false;
		result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_RECORDING);
		if (SL_RESULT_SUCCESS != result) return false;

		bufferQueue->notifyBuffer();
		time = 0;
		return true;
	}
	return false;
}

void AudioRecorder::closeAudioDevice()
{
	// destroy audio recorder object, and invalidate all associated interfaces
	if (recorderObject != nullptr) {
		(*recorderObject)->Destroy(recorderObject);
		recorderObject = nullptr;
		recorderRecord = nullptr;
		recorderBufferQueue = nullptr;
	}

	AudioBase::closeAudioDevice();
}

