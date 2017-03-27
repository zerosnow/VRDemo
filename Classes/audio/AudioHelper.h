#pragma once

#include "AudioPlayer.h"
#include "AudioRecord.h"
#include <iostream>

using namespace std;

class AudioHelper
{
public:
	AudioHelper();
	~AudioHelper();

	static AudioHelper *getInstance();

	void startPlay(string fileName);
	void startPlayAssert(string fileName);
	void startRecord(string fileName);
	void stopRecord();
	void stopPlay();

	void playForward();
	void playBack();
	void playPause();
	void playResume();
	void recordBack();
	void recordPause();
	void recordResume();
	void changePlayState();
	void changeRecordState();
	double getPlayTime();
	double getRecordTime();

	string playFileName;
	string recordFileName;
	FILE *playFilePointer;
	FILE *recordFilePointer;
	bool isRecording = false;
	bool isPlaying = false;
	void *playThreadLock;
	void *recordThreadLock;

	typedef enum {
		STATE_PAUSE,
		STATE_RUN
	}State;
	State playState;
	State recordState;

	static AudioHelper *audioHelper;
	AudioPlayer *audioPlayer;
	AudioRecorder *audioRecord;

private:
	const long offsetForOne = 25000;
};