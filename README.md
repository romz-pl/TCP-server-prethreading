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


## TCP Client and TCP Server communication

Each time we run the client, we specify:
* the hostname or IP address of the server; 
* the server’s port;
* the number of children for the client to `fork` (allowing us to initiate multiple 
connections to the same server concurrently); 
* the number of requests each child should send to the server; 
* and the number of bytes to request the server to return each time.

The parent calls `fork` for each child, and each child establishes the specified number 
of connections with the server. On each connection, the child sends a line specifying
the number of bytes for the server to return, and then the child reads that amount of
data from the server. The parent just `wait`s for all the children to terminate. Notice
that the client closes each TCP connection, so TCP’s `TIME_WAIT` state occurs on the
client, not on the server. This is a difference between our client/server and normal
HTTP connections.

For example, executing the client as
```
% ./client 192.168.1.20 8888 5 500 4000
```
it creates 2,500 TCP connections to the server: 500 connections from each of five children. 
On each connection, 5 bytes are sent from the client to the server ("4000\n’") and
4,000 bytes are transferred from the server back to the client.

## How to build

In order to build the system execute the following commands.

1.  Clone the repo from github:
```
git clone git@github.com:romz-pl/TCP-server-prethreading.git
```

2. Create new directory for building purposes outside of the source code directory:
```
mkdir build && cd build
```

3. Since the project is build by `cmake`, execute the following two commands
for configuration, compilation and linking the binaries:
```
cmake ../TCP-server-prethreading
make
```

4. The final binaries are: `build/src/server` and `build/src/client`.



## References

* Warren W. Gay, _Linux Socket Programming by Example_, (2000)

* S. Walton, _Linux Socket Programming_, (2001)

* M. J. Donahoo, _TCP/IP Sockets in C, Practical Guide for Programmers_, (2001)

* W.R. Stevens, B. Fenner, A.M. Rudoff, _UNIX Network Programming_, Volume 1, (2003) and web site for this book http://www.unpbook.com/

* See also W. Richard Stevens' Home Page http://www.kohala.com/start/

