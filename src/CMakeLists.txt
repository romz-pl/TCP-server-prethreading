SET( EXE_NAME server )

add_executable( server
    addrlen.c
    err_quit.c
    listenfd.c
    mlock.c
    nthreads.c
    pr_cpu_time.c
    readline.c
    server.c
    sig_int.c
    tcp_listen.c
    thread_make.c
    tptr.c
    thread_main.c
    web_child.c
    writen.c
)

add_executable( client
    client.c
    err_quit.c
    readn.c
    tcp_connect.c
)

