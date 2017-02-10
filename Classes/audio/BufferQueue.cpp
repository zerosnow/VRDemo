#include "BufferQueue.h"
#include "../logutil.h"
#include <stdlib.h>
#include "thread.h"

BufferQueue::BufferQueue()
{

}

BufferQueue::~BufferQueue()
{
	if (lock != nullptr) {
		notifyThreadLock(lock);
		destroyThreadLock(lock);
		lock = nullptr;
	}

	if (buffer[0] != nullptr) {
		free(buffer[0]);
		buffer[0] = nullptr;
	}

	if (buffer[1] != nullptr) {
		free(buffer[1]);
		buffer[1] = nullptr;
	}
}

bool BufferQueue::init(int bufferSize, int currentIndex)
{
	lock = createThreadLock();
	if (bufferSize != 0)
	{
		this->bufferSize = bufferSize;
		this->buffer[0] = (short *)calloc(bufferSize, sizeof(short));
		this->buffer[1] = (short *)calloc(bufferSize, sizeof(short));
		if (buffer[0] == nullptr || buffer[1] == nullptr)
		{
			LOGD("buffer fail");
			return false;
		}
		this->currentIndex = currentIndex;
		currentBuffer = 0;

		return true;
	}
	else {
		LOGD("buffer size is 0");
		return false;
	}
}

short *BufferQueue::waitBuffer(SLAndroidSimpleBufferQueueItf bufferQueue)
{
	short *buffer;
	waitThreadLock(lock);
	(*bufferQueue)->Enqueue(bufferQueue, this->buffer[currentBuffer], bufferSize * sizeof(short));
	buffer = this->buffer[currentBuffer];
	currentBuffer = currentBuffer ? 0 : 1;
	return buffer;
}

void BufferQueue::notifyBuffer()
{
	notifyThreadLock(lock);
}

short *BufferQueue::getBuffer()
{
	return buffer[currentBuffer];
}