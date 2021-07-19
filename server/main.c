#include "addrlen.h"
#include "err_quit.h"
#include "listenfd.h"
#include "nthreads.h"
#include "tcp_listen.h"
#include "thread_make.h"
#include "tptr.h"
#include "sig_int.h"

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h> 


int
main(int argc, char **argv)
{
	int		i;
	void	sig_int(int), thread_make(int);

	if (argc == 3)
    {
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
    }
	else if (argc == 4)
    {
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
    }
	else
    {
		err_quit("usage: server [ <host> ] <port#> <#threads>");
    }

	nthreads = atoi(argv[argc-1]);
	tptr = calloc(nthreads, sizeof(Thread));
    if(tptr == NULL)
    {
        err_quit("calloc failed");
    }

	for (i = 0; i < nthreads; i++)
    {
		thread_make(i);			/* only main thread returns */
    }

	signal(SIGINT, sig_int);

	for ( ; ; )
		pause();	/* everything done by threads */
}
