#include "socket.h"
#include <string.h>
#include <stdio.h>

#if defined __CYGWIN__ || defined __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#elif defined _WIN32
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif


int
le_con(const char *ip, int port)
{
    //return connect();
    return 0;
}

int
le_write(int fd_sock, const char *buff, size_t size)
{
	return 0;
}

int
le_read(int fd_sock, char *buff, size_t size)
{
	return 0;
}

int
le_ping(const char *ip)
{
	return 0;
}

int
le_listen(int port, int backlog)
{
#if defined __linux__ || defined __CYGWIN__
	int fd_sock;
	socklen_t addrlen;
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
	if (-1 == listen(fd_sock, backlog)) { 				//listen will block the program.
		printf("libedtp: le_listen: socket listen error! ");
	}
	return fd_sock;
#elif defined _WIN32 						//not tested.
	WSADATA wdata;
	SOCKADDR_IN server_addr;
	SOCKET server_socket;
	int addr_len = sizeof(SOCKADDR_IN);

	int status = WSAStartup(MAKEWORD(2, 0), &wdata);
	if (status != 0)
		return -1;

	if (LOBYTE(wdata.wVersion) != 2 || HIBYTE(wdata.wVersion) != 0) {
		WSACleanup();
		return -1;
	}

	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	bind(server_socket, (SOCKADDR *)&server_addr, addr_len);
	listen(server_socket, backlog);
	return (int)server_socket;
#endif
}

void
le_close(int fd_sock)
{
#if defined __linux__ || defined __CYGWIN__
	close(fd_sock);
#elif defined _WIN32
	closesocket(fd_sock);
#endif
}

void
le_clean()
{
#if defined _WIN32
	WSACleanup();
#endif
}

#if defined __CYGWIN__ || defined __linux__
struct sockaddr_in
le_accept(int *fd_sock, int type)
{
	socklen_t addrlen;
	struct sockaddr_in addr;
	addrlen = sizeof(sockaddr_in);

	*fd_sock = accept(*fd_sock, (sockaddr *)&addr, &addrlen);
	if (*fd_sock == -1) {
		printf("libedtp: le_listen: socket accept error!");
		*fd_sock = -1;
	}
	return addr;
}
#elif defined _WIN32
struct SOCKADDR_IN
le_accept(int *fd_sock, int type)
{
	SOCKADDR_IN addr;
	int addr_len = sizeof(SOCKADDR_IN);
	server_socket = accept(*fd_sock, &addr, &addr_len);
	return addr;
}
#endif
