#ifndef LIBEDTP_SOCKET_H
#define LIBEDTP_SOCKET_H

int le_con(const char *ip, int port);

int le_write(int fd_sock, const char *buff, size_t size);

int le_read(int fd_sock, char *buff, size_t size);

int le_ping(const char *ip);

int le_listen(int port, int backlog = 256);


#endif
