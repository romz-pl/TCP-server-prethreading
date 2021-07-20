SET( EXE_NAME server )

add_executable( ${EXE_NAME}
    addrlen.c
    err_quit.c
    listenfd.c
    main.c
    mlock.c
    nthreads.c
    pr_cpu_time.c
    readline.c
    sig_int.c
    tcp_listen.c
    thread_make.c
    tptr.c
    thread_main.c
    web_child.c
    writen.c
)

