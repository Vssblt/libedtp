#include "socket.h"
#include <string.h>
#include <stdio.h>

#if defined __CYGWIN__ || defined __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#elif defined _WIN32
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#endif


int
le_con(const char *ip, int port)
{
    //return connect();
}

int
le_write(int fd_sock, const char *buff, size_t size)
{
}

int
le_read(int fd_sock, char *buff, size_t size)
{
}

int
le_ping(const char *ip)
{
}

int
le_listen(int port, int backlog)
{
#if defined __linux__ || defined __CYGWIN__
	int fd_sock;
	size_t addrlen;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(addr.sin_zero), 0, 8);
	addrlen = sizeof(sockaddr_in);

	if (-1 == (fd_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) {
		printf("libedtp: le_listen: fd_socket error.");
	}
	if (-1 == bind(fd_sock, (sockaddr *)&addr, addrlen) ) {
		printf("libedtp: le_listen: socket bind error.");
	}
	if (-1 == listen(fd_sock, backlog)) {
		printf("libedtp: le_listen: socket listen error! ");
	}
	if (-1 == accept(fd_sock, (sockaddr *)&addr, addrlen)) {
		printf("libedtp: le_listen: socket accept error!");
	}
	return fd_sock;
#elif defined _WIN32

#endif
}
