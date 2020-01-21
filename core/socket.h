#ifndef LIBEDTP_SOCKET_H
#define LIBEDTP_SOCKET_H

#include <stddef.h>

int le_con(const char *ip, int port);

int le_write(int fd_sock, const char *buff, size_t size);

int le_read(int fd_sock, char *buff, size_t size);

int le_ping(const char *ip);

/* If function return -1, it means failed, otherwise successed. */
int le_listen(int port, int backlog = 256);

void le_clean();

void le_close(int fd_sock);

#if defined __CYGWIN__ || defined __linux__
struct sockaddr_in le_accept(int *fd_sock, int type); 
#elif defined _WIN32
struct SOCKADDR_IN le_accept(int *fd_sock, int type);
#endif

#endif
