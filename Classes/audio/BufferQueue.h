#pragma once

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class BufferQueue
{
public:
	BufferQueue();
	~BufferQueue();

	bool init(int bufferSize, int currentIndex);
	short *waitBuffer(SLAndroidSimpleBufferQueueItf bufferQueue);
	short *getBuffer();
	void notifyBuffer();

	// buffer indexes
	int currentIndex;

	// size of buffers
	int bufferSize;
private:
	
	// current buffer half (0, 1)
	int currentBuffer;

	// buffers
	short *buffer[2];

	// locks
	void* lock;
};