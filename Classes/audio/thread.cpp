#include "thread.h"
#include <stdlib.h>

//----------------------------------------------------------------------
// thread Locks
// to ensure synchronisation between callbacks and processing code
void* createThreadLock(void)
{
	threadLock  *p;
	p = (threadLock*)malloc(sizeof(threadLock) + 1);
	if (p == NULL)
		return NULL;
	memset(p, 0, sizeof(threadLock));
	if (pthread_mutex_init(&(p->m), (pthread_mutexattr_t*)NULL) != 0) {
		free((void*)p);
		return NULL;
	}
	if (pthread_cond_init(&(p->c), (pthread_condattr_t*)NULL) != 0) {
		pthread_mutex_destroy(&(p->m));
		free((void*)p);
		return NULL;
	}
	p->s = (unsigned char)1;

	return p;
}

int waitThreadLock(void *lock)
{
	threadLock  *p;
	int retval = 0;
	p = (threadLock*)lock;
	pthread_mutex_lock(&(p->m));
	while (!p->s) {
		pthread_cond_wait(&(p->c), &(p->m));
	}
	p->s = (unsigned char)0;

	pthread_mutex_unlock(&(p->m));

	return 0;
}

void notifyThreadLock(void *lock)
{
	threadLock *p;
	p = (threadLock*)lock;
	pthread_mutex_lock(&(p->m));
	p->s = (unsigned char)1;
	pthread_cond_signal(&(p->c));
	pthread_mutex_unlock(&(p->m));
}

void destroyThreadLock(void *lock)
{
	threadLock  *p;
	p = (threadLock*)lock;
	if (p == NULL)
		return;
	notifyThreadLock(p);
	pthread_cond_destroy(&(p->c));
	pthread_mutex_destroy(&(p->m));
	free(p);
}