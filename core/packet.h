#ifndef LIBEDTP_PACKET_H
#define LIBEDTP_PACKET_H

/* This function listen on a port to accept connection requests.
 * Callback is a function pointer, if function listen successful 
 * and callback is not NULL, callback will be trigered in a new 
 * thead, otherwise this function will return a fd of sokcet. */
int listen(int port, void *callback = NULL, int backlog = 256);

/* This function get current block, and pointer to next block in the 
 * socket buffer. */
size_t get_block(int fd_sock, void *buff, size_t max_size = -1);

/* This function return zero when the block is not ready to be read,
 * otherwise it will return a non-zero number. */
int ready_read(int fd_sock);

/* This function return a type of current block. */ 
int read_type(int fd_sock);

size_t read_sizeof(int fd_sock);

#endif

