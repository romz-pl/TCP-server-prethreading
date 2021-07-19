#include "sig_int.h"

#include "nthreads.h"
#include "pr_cpu_time.h"
#include "tptr.h"

#include <stdlib.h>
#include <stdio.h>

void
sig_int(int signo)
{
	int		i;

	pr_cpu_time();

	for (i = 0; i < nthreads; i++)
		printf("thread %d, %ld connections\n", i, tptr[i].thread_count);

	exit(0);
}

