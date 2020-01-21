#include "packet.h"
#include "socket.h"
#include "thread.h"
#include "common.h"

size_t read_sizeof(int fd_sock);

int
listen(int port, void *callback, int backlog)
{
	int fd_sock = le_listen(port, backlog);
	if (callback != NULL && fd_sock != -1) {
		new_thread(callback, &fd_sock);
	}
	return fd_sock;
}

int 
accept(int fd, void *addr_info, void *callback)
{

	return 0;
}

size_t 
read_block(int fd_sock, void *buff, size_t max_size)
{
	while (!ready_read(fd_sock));// sleep(1);
	int type = read_type(fd_sock);
	if (type > 65535 || type < 0) {
		return 0;
	}
	if (edtp_type[type] == 0) {
		return 0;
	}

	return le_read(fd_sock, (char *)buff, min(max_size, (size_t)(edtp_type[type])));
}

int
ready_read(int fd_sock)
{
	size_t size = read_sizeof(fd_sock);
	size_t current = le_body_size(fd_sock);
	return size <= current; 
}

int 
read_type(int fd_sock)
{
	return 0;
}

size_t
read_sizeof(int fd_sock)
{
	return 0;
}

size_t
le_body_size(int)
{
	return 0;
}

void
struct_register(const char *id, const char *member_length)
{

}


