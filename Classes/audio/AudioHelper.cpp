
#include "AudioHelper.h"
#include "utils/logutil.h"
#include <pthread.h>
#include "cocos2d.h"
#include "wav.h"
#include "thread.h"

using namespace cocos2d;

static void *threadStartPlay(void *param);
static void *threadStartRecord(void *param);

AudioHelper::AudioHelper()
{
}

AudioHelper::~AudioHelper()
{
}

AudioHelper *AudioHelper::audioHelper = new AudioHelper();
AudioHelper *AudioHelper::getInstance()
{
	if (audioHelper == nullptr)
	{
		audioHelper = new AudioHelper();
	}
	return audioHelper;
}

void AudioHelper::startPlay(string fileName)
{
	if (isPlaying)
	{
		LOGD("isPlaying");
		return;
	}
	else {
		LOGD("begin play");
	}
	
	this->playFileName = fileName;
	pthread_t thread = 0;
	int iret = pthread_create(&thread, NULL, threadStartPlay, audioHelper);
	if (iret)
	{
		LOGE("error while create thread...");
	}
}

void AudioHelper::startPlayAssert(string fileName)
{
	string fullFileName = FileUtils::getInstance()->fullPathForFilename(fileName);

	Data data = FileUtils::getInstance()->getDataFromFile(fullFileName);

	std::string destPath = FileUtils::getInstance()->getWritablePath();
	destPath += fileName;
	FILE *fp = fopen(destPath.c_str(), "w+");
	fwrite(data.getBytes(), sizeof(char), data.getSize(), fp);
	fclose(fp);
	data.clear();

	startPlay(destPath);
}

void AudioHelper::startRecord(string fileName)
{
	LOGD("begin record: %s", fileName.c_str());

	this->recordFileName = fileName;
	pthread_t thread = 0;
	int iret = pthread_create(&thread, NULL, threadStartRecord, audioHelper);
	if (iret)
	{
		LOGE("error while create thread...");
	}
}

void AudioHelper::stopRecord()
{
	isRecording = false;
}

void AudioHelper::stopPlay()
{
	isPlaying = false;
}

void AudioHelper::playForward()
{
	fseek(playFilePointer, offsetForOne, 1);
	//sizeof结果为unsign long类型，如果不强转类型，被除数会自动提升为unsign long类型，如果被除数为负数，则会出现错误。
	audioPlayer->addTimeSize((int)offsetForOne / (long)(sizeof(short)));	
}

void AudioHelper::playBack()
{
	fseek(playFilePointer, -offsetForOne, 1);
	audioPlayer->addTimeSize(-offsetForOne / (long)(sizeof(short)));
}

void AudioHelper::playPause()
{
	playState = AudioHelper::STATE_PAUSE;
}

void AudioHelper::playResume()
{
	if (playState == AudioHelper::STATE_PAUSE)
	{
		playState = AudioHelper::STATE_RUN;
		notifyThreadLock(playThreadLock);
	}
}

void AudioHelper::recordBack()
{
	fseek(recordFilePointer, -offsetForOne, 1);
	audioRecord->addTimeSize(-(int)offsetForOne / (long)(sizeof(short)));
}

void AudioHelper::recordPause()
{
	recordState = AudioHelper::STATE_PAUSE;
}

void AudioHelper::recordResume()
{
	if (recordState == AudioHelper::STATE_PAUSE)
	{
		recordState = AudioHelper::STATE_RUN;
		notifyThreadLock(recordThreadLock);
	}
}

void AudioHelper::changePlayState()
{
	if (playState == AudioHelper::STATE_PAUSE)
	{
		playState = AudioHelper::STATE_RUN;
		notifyThreadLock(playThreadLock);
	} else if (playState == AudioHelper::STATE_RUN){
		playState = AudioHelper::STATE_PAUSE;
	}
}

void AudioHelper::changeRecordState()
{
	if (recordState == AudioHelper::STATE_PAUSE)
	{
		recordState = AudioHelper::STATE_RUN;
		notifyThreadLock(recordThreadLock);
	} else if (recordState == AudioHelper::STATE_RUN){
		recordState = AudioHelper::STATE_PAUSE;
	}
}

double AudioHelper::getPlayTime()
{
	return audioPlayer->getTime();
}

double AudioHelper::getRecordTime()
{
	return audioRecord->getTime();
}

static void *threadStartPlay(void *param)
{
	AudioHelper *audioHelper = (AudioHelper *)param;
	audioHelper->playFilePointer = fopen(audioHelper->playFileName.c_str(), "rb");
	if (audioHelper->playFilePointer == NULL) {
		LOGD("cannot open file (%s) !\n", audioHelper->playFileName.c_str());
		return nullptr;
	}

	audioHelper->audioPlayer = new AudioPlayer();

	struct wavFileHeader header;
	if (audioHelper->playFileName.find(".wav") != string::npos)
	{
		if (fread((void *)(&header), sizeof(struct wavFileHeader), 1, audioHelper->playFilePointer) != 1) {
			LOGD("failed to read header data \n ");
			return nullptr;
		}

		LOGD("%s, %d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %s, %d", header.ChunkID, header.ChunkSize, header.Format, header.Subchunk1ID, header.Subchunk1Size, header.AudioFormat,
			header.NumChannels, header.SampleRate, header.ByteRate, header.BlockAlign, header.BitsPerSample, header.Subchunk2ID, header.Subchunk2Size);

		audioHelper->audioPlayer->openAudioDevice(header.SampleRate * 1000, header.NumChannels, header.SampleRate * 20 / 1000);

	}
	else {
		audioHelper->audioPlayer->openAudioDevice();
	}

	int samples;
	short *buffer = new short[audioHelper->audioPlayer->getBufferFrame()];
	audioHelper->isPlaying = true;
	audioHelper->playState = AudioHelper::STATE_RUN;
	audioHelper->playThreadLock = createThreadLock();
	while (audioHelper->isPlaying && !feof(audioHelper->playFilePointer)) {
		if (audioHelper->playState == AudioHelper::STATE_PAUSE)
		{
			waitThreadLock(audioHelper->playThreadLock);
		}
		if (fread((unsigned char *)buffer, audioHelper->audioPlayer->getBufferFrame() * sizeof(short), 1, audioHelper->playFilePointer) != 1) {
			LOGD("failed to read data \n ");
			break;
		}
		samples = audioHelper->audioPlayer->AudioOut(buffer, audioHelper->audioPlayer->getBufferFrame());
		if (samples < 0) {
			LOGD("android_AudioOut failed !\n");
		}
	}

	destroyThreadLock(audioHelper->playThreadLock);
	audioHelper->audioPlayer->closeAudioDevice();
	fclose(audioHelper->playFilePointer);
	delete audioHelper->audioPlayer;

	LOGD("nativeStartPlayback completed !");

	return nullptr;
}

static void *threadStartRecord(void *param)
{
	AudioHelper *audioHelper = (AudioHelper *)param;
	audioHelper->recordFilePointer = fopen(audioHelper->recordFileName.c_str(), "wb");
	if (audioHelper->recordFilePointer == NULL) {
		LOGD("cannot open file (%s)\n", audioHelper->recordFileName.c_str());
		return nullptr;
	}

	audioHelper->audioRecord = new AudioRecorder();
	audioHelper->audioRecord->openAudioDevice();

	int samples;
	short *buffer = new short[audioHelper->audioRecord->getBufferFrame()];
	audioHelper->isRecording = true;
	audioHelper->recordState = AudioHelper::STATE_RUN;
	audioHelper->recordThreadLock = createThreadLock();
	while (audioHelper->isRecording) {
		if (audioHelper->recordState == AudioHelper::STATE_PAUSE)
		{
			waitThreadLock(audioHelper->recordThreadLock);
		}
		samples = audioHelper->audioRecord->AudioIn(buffer, audioHelper->audioRecord->getBufferFrame());
		if (samples < 0) {
			LOGD("android_AudioIn failed !\n");
			break;
		}
		if (fwrite((unsigned char *)buffer, samples * sizeof(short), 1, audioHelper->recordFilePointer) != 1) {
			LOGD("failed to save captured data !\n ");
			break;
		}
	}

	destroyThreadLock(audioHelper->recordThreadLock);
	audioHelper->audioRecord->closeAudioDevice();
	fclose(audioHelper->recordFilePointer);
	delete audioHelper->audioRecord;

	LOGD("nativeStartCapture completed !");

	return nullptr;
}


