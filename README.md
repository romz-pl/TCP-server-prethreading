# The concurrent TCP server with prethreading. 

The server creates a pool of available threads when it starts, and one thread from the pool handles each client.

## Rationale

On a system that supports threads, it is reasonable to
expect a speedup by creating a pool of threads when the server starts, instead of
creating a new thread for every client. The basic design of this server is to create a pool
of threads and then let each thread call `accept`. Instead of having each thread block in
the call to `accept`, we will use a mutex lock that allows only
one thread at a time to call `accept`.

## References

* Warren W. Gay, _Linux Socket Programming by Example_, (2000)

* S. Walton, _Linux Socket Programming_, (2001)

* M. J. Donahoo, _TCP/IP Sockets in C, Practical Guide for Programmers_, (2001)

* W.R. Stevens, B. Fenner, A.M. Rudoff, _UNIX Network Programming_, Volume 1, (2003)

* See also W. Richard Stevens' Home Page http://www.kohala.com/start/

