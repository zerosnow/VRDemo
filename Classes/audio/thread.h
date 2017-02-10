#ifndef _CUSTOM_THREAD
#define _CUSTOM_THREAD

#include <pthread.h>

typedef struct threadLock_ {
	pthread_mutex_t m;
	pthread_cond_t  c;
	unsigned char   s;
} threadLock;

void* createThreadLock(void);
int waitThreadLock(void *lock);
void notifyThreadLock(void *lock);
void destroyThreadLock(void *lock);

#endif