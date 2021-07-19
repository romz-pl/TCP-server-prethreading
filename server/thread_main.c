#include "thread_main.h"

#include "addrlen.h"
#include "err_quit.h"
#include "listenfd.h"
#include "web_child.h"
#include "mlock.h"
#include "tptr.h"

#include <pthread.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *
thread_main(void *arg)
{
	int				connfd;
	socklen_t		clilen;
	struct sockaddr	*cliaddr;

	cliaddr = malloc(addrlen);
    if(cliaddr == NULL)
    {
        err_quit("malloc failed");
    }

	printf("thread %d starting\n", (int) arg);
	for ( ; ; ) {
		clilen = addrlen;
    	pthread_mutex_lock(&mlock);
		connfd = accept(listenfd, cliaddr, &clilen);
		pthread_mutex_unlock(&mlock);
		tptr[(int) arg].thread_count++;

		web_child(connfd);		/* process request */
		close(connfd);
	}
}

