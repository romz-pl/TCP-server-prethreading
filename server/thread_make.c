#include "thread_make.h"

#include "thread_main.h"
#include "tptr.h"

#include <pthread.h>

void
thread_make(int i)
{
	void	*thread_main(void *);

	pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *) i);
	return;		/* main thread returns */
}

