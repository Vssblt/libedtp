#ifndef LIBEDTP_PACKET_H
#define LIBEDTP_PACKET_H

int listen(int port, void *callback = NULL, int fd = -1, int backlog = 256);

size_t get_block(int fd_sock, void *buff, size_t max_size = -1);
int ready_read(int fd_sock);
//short int read_type(int fd_sock);
i//nt read_head(int fd_sock);

#endif

