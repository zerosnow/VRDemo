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

	string fileName;
	bool isRecording = false;
	bool isPlaying = false;

	static AudioHelper *audioHelper;
	AudioPlayer *audioPlayer;
	AudioRecorder *audioRecord;
};