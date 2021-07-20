#include "web_child.h"

#include "err_quit.h"
#include "MAXLINE.h"
#include "readline.h"
#include "writen.h"

#include <stdlib.h>  

#define	MAXN	16384		/* max # bytes client can request */

void web_child(int sockfd)
{
	int			ntowrite;
	ssize_t		nread;
	char		line[MAXLINE], result[MAXN];

	for ( ; ; ) {
        nread = readline(sockfd, line, MAXLINE);
		if ( nread  == 0)
        {
			return;		/* connection closed by other end */
        }

        if ( nread < 0 )
        {
            err_quit("readline error");
        }

        /* 4line from client specifies #bytes to write back */
		ntowrite = atol(line);
		if ((ntowrite <= 0) || (ntowrite > MAXN))
        {
			err_quit("client request for %d bytes", ntowrite);
        }

		if( writen(sockfd, result, ntowrite) != ntowrite )
        {
            err_quit("writen failed");
        }
	}
}

