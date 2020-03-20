#ifndef LIBEDTP_PACKET_H
#define LIBEDTP_PACKET_H
#include <stddef.h>
#include <netinet/in.h>

/* This function listen on a port to accept connect requests.
 * Callback is a function pointer, if callback is not NULL, 
 * callback will be triggered in a new thread. if function 
 * succeeds, the function will return a fd of the sokcet, otherwise
 * the function will return -1. */
int listen(int port, void *callback = NULL, int backlog = 256);

/* If callback is NULL, this function will block the thread to accept connect requests
 * and never return. When connection is created, callback will be 
 * triggered in a new thread, addr_info will save the client address 
 * information. */
int accept(int fd, sockaddr_in *addr_info = NULL, void *callback = NULL);

int connect(const char* ip, int port);

/* This function get current block, and pointer to next block in the 
 * socket buffer. */
size_t read_block(int fd_sock, void *buff, size_t max_size = -1);

/* This function return zero when the block is not ready to be read,
 * otherwise it will return a non-zero number. */
int ready_read(int fd_sock);

/* This function return a type of current block. */ 
int read_type(int fd_sock);

/* If you want*/
void struct_register(const char *id, const char *member_length);

size_t read_sizeof(int fd_sock);

size_t le_body_size(int);

struct Struct_Table {
//	const 
	int test;
};
static struct Struct_Table struct_table;
#endif

