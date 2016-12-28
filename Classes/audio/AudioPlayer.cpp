#include "AudioPlayer.h"
#include "../logutil.h"

AudioPlayer::AudioPlayer()
{
	LOGD("AudioPlayer");
}

AudioPlayer::~AudioPlayer()
{
}

int AudioPlayer::AudioOut(short *buffer, int size)
{
	short *outBuffer;
	int i, bufsamps = bufferQueue->bufferSize, index = bufferQueue->currentIndex;
	if (bufsamps == 0)  return 0;

	outBuffer = bufferQueue->getBuffer();
	for (i = 0; i < size; i++) {
		outBuffer[index++] = buffer[i];
		if (index >= bufferQueue->bufferSize) {
			outBuffer = bufferQueue->waitBuffer(bqPlayerBufferQueue);
			index = 0;
		}
	}
	bufferQueue->currentIndex = index;
	time += (double)size / (sampleRate*channels);
	return i;
}

bool AudioPlayer::openAudioDevice()
{
	return this->openAudioDevice(DEFAULT_SAMPLERATE, DEFAULT_CHANNELS, DEFAULT_FRAME_SIZE);
}

bool AudioPlayer::openAudioDevice(SLuint32 sampleRate, SLuint32 channels, SLuint32 bufferFrames)
{
	if (!AudioBase::openAudioDevice(sampleRate, channels, bufferFrames))
	{
		LOGE("AudioBase::openAudioDevice ERROR");
		return false;
	}


	if (!bufferQueue->init(channels * bufferFrames, 0))
	{
		LOGE("bufferQueue->init ERROR");
		return false;
	}

	if (channels != 0)
	{
		SLresult result;

		SLDataLocator_BufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		const SLInterfaceID ids[] = { SL_IID_VOLUME };
		const SLboolean req[] = { SL_BOOLEAN_FALSE };
		result = (*mEngine)->CreateOutputMix(mEngine, &outputMixObject, 1, ids, req);
		if (result != SL_RESULT_SUCCESS) return false;


		result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS) return false;

		SLuint32 channelMask;
		if (channels > 1)
			channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
		else channelMask = SL_SPEAKER_FRONT_CENTER;

		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, channels, sampleRate,
			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
			channelMask, SL_BYTEORDER_LITTLEENDIAN };

		SLDataSource audioSrc = { &loc_bufq, &format_pcm };

		// configure audio sink
		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
		SLDataSink audioSnk = { &loc_outmix, nullptr };

		// create audio player
		const SLInterfaceID ids1[] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		const SLboolean req1[] = { SL_BOOLEAN_TRUE };
		result = (*mEngine)->CreateAudioPlayer(mEngine, &bqPlayerObject, &audioSrc, &audioSnk,
			1, ids1, req1);
		if (result != SL_RESULT_SUCCESS) return false;

		result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS) return false;

		// get the play interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &(bqPlayerPlay));
		if (result != SL_RESULT_SUCCESS) return false;

		// get the buffer queue interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
			&(bqPlayerBufferQueue));
		if (result != SL_RESULT_SUCCESS) return false;

		// register callback on the buffer queue
		result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, AudioBase::bqCallBack, bufferQueue);
		if (result != SL_RESULT_SUCCESS) return false;

		//
		result = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
		if (result != SL_RESULT_SUCCESS) return false;

		// set the player's state to playing
		result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
		if (result != SL_RESULT_SUCCESS) return false;
		
		bufferQueue->notifyBuffer();
		time = 0;
		return true;
	}
	return false;
}

void AudioPlayer::closeAudioDevice()
{
	if (bqPlayerObject != nullptr) {
		(*bqPlayerObject)->Destroy(bqPlayerObject);
		bqPlayerObject = nullptr;
		bqPlayerPlay = nullptr;
		bqPlayerBufferQueue = nullptr;
		bqPlayerEffectSend = nullptr;
	}

	if (outputMixObject != nullptr) {
		(*outputMixObject)->Destroy(outputMixObject);
		outputMixObject = nullptr;
	}

	AudioBase::closeAudioDevice();
}