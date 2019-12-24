#include "packet.h"
#include "socket.h"

int
listen(int port, void *callback, int fd, int backlog)
{
	int fd_sock = le_listen(port, backlog);
	if (callback != NULL) {
		callback(fd_sock);
	}
	return fd_sock;
}

size_t 
read_block(int fd_sock, void *buff, size_t max_size)
{
	while (!ready_read());
	int type = read_type(fd_sock);
	if (edtp_type[type] == -1) {
		return 0;
	}



}

int
ready_read(int fd_sock)
{
	return 1;
}

short int 
read_type(int fd_sock)
{
	return 0;
}

int
read_head(int fd_sock, void *buff)
{
	return 0;
}
