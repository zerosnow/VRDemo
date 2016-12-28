
#include "AudioHelper.h"
#include "../logutil.h"
#include <pthread.h>
#include "cocos2d.h"
#include "wav.h"

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
	
	this->fileName = fileName;
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
	LOGD("begin record");

	this->fileName = fileName;
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


static void *threadStartPlay(void *param)
{
	AudioHelper *audioHelper = (AudioHelper *)param;
	FILE *fp = fopen(audioHelper->fileName.c_str(), "rb");
	if (fp == NULL) {
		LOGD("cannot open file (%s) !\n", audioHelper->fileName.c_str());
		return nullptr;
	}

	
	
	audioHelper->audioPlayer = new AudioPlayer();

	struct wavFileHeader header;
	if (audioHelper->fileName.find(".wav") != string::npos)
	{
		if (fread((void *)(&header), sizeof(struct wavFileHeader), 1, fp) != 1) {
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
	while (audioHelper->isPlaying && !feof(fp)) {
		if (fread((unsigned char *)buffer, audioHelper->audioPlayer->getBufferFrame() * sizeof(short), 1, fp) != 1) {
			LOGD("failed to read data \n ");
			break;
		}
		samples = audioHelper->audioPlayer->AudioOut(buffer, audioHelper->audioPlayer->getBufferFrame());
		if (samples < 0) {
			LOGD("android_AudioOut failed !\n");
		}
	}

	audioHelper->audioPlayer->closeAudioDevice();
	fclose(fp);
	delete audioHelper->audioPlayer;

	LOGD("nativeStartPlayback completed !");

	return nullptr;
}

static void *threadStartRecord(void *param)
{
	AudioHelper *audioHelper = (AudioHelper *)param;
	FILE * fp = fopen(audioHelper->fileName.c_str(), "wb");
	if (fp == NULL) {
		LOGD("cannot open file (%s)\n", audioHelper->fileName.c_str());
		return nullptr;
	}

	audioHelper->audioRecord = new AudioRecorder();
	audioHelper->audioRecord->openAudioDevice();

	int samples;
	short *buffer = new short[audioHelper->audioRecord->getBufferFrame()];
	audioHelper->isRecording = true;
	while (audioHelper->isRecording) {
		samples = audioHelper->audioRecord->AudioIn(buffer, audioHelper->audioRecord->getBufferFrame());
		if (samples < 0) {
			LOGD("android_AudioIn failed !\n");
			break;
		}
		if (fwrite((unsigned char *)buffer, samples * sizeof(short), 1, fp) != 1) {
			LOGD("failed to save captured data !\n ");
			break;
		}
	}

	audioHelper->audioRecord->closeAudioDevice();
	fclose(fp);
	delete audioHelper->audioRecord;

	LOGD("nativeStartCapture completed !");

	return nullptr;
}