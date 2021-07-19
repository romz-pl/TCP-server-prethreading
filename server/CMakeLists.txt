SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    addrlen.c
    err_quit.c
    listenfd.c
    main.c
    nthreads.c
    pr_cpu_time.c
    sig_int.c
    tcp_listen.c
    thread_make.c
    tptr.c
)

