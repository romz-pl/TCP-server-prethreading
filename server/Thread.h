#pragma once

#include <pthread.h>

typedef struct {
    pthread_t		thread_tid;		/* thread ID */
    long			thread_count;	/* # connections handled */
} Thread;

