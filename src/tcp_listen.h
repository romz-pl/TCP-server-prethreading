#pragma once

#include <sys/socket.h>

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);

