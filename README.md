# The concurrent TCP server with prethreading 

The server creates a pool of available threads when it starts, and one thread from the pool handles each client.

## Rationale

On a system that supports threads, it is reasonable to
expect a speedup by creating a pool of threads when the server starts, instead of
creating a new thread for every client. The basic design of this server is to create a pool
of threads and then let each thread call `accept`. Instead of having each thread block in
the call to `accept`, we will use a mutex lock that allows only
one thread at a time to call `accept`.

## Berkeley-derived kernel

On a Berkeley-derived kernel, we do not need any locking around the call to `accept` and can
write a code without any mutex locking and unlocking. Doing so, however,
increases the process control CPU time. If we look at the two components of the CPU time, the
user time and the system time, without any locking, the user time decreases (because the locking 
is done in the threads library, which executes in user space), but the system time increases
(the kernel’s thundering herd as all threads blocked in accept are awakened when a connection arrives). 
Since some form of mutual exclusion is required to return each connection to a
single thread, it is faster for the threads to do this themselves than for the kernel.

## References

* Warren W. Gay, _Linux Socket Programming by Example_, (2000)

* S. Walton, _Linux Socket Programming_, (2001)

* M. J. Donahoo, _TCP/IP Sockets in C, Practical Guide for Programmers_, (2001)

* W.R. Stevens, B. Fenner, A.M. Rudoff, _UNIX Network Programming_, Volume 1, (2003) and web site for this book http://www.unpbook.com/

* See also W. Richard Stevens' Home Page http://www.kohala.com/start/

