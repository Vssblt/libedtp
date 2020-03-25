#include "packet.h"
#include "socket.h"
#include "thread.h"
#include "common.h"
#include <malloc.h>

size_t read_sizeof(int fd_sock);

int
listen(int port, void *callback, int backlog)
{
	int *fd_sock = (int *)malloc(sizeof(int));
	*fd_sock = le_listen(port, backlog);
	if (callback != NULL && *fd_sock != -1) {
		int ret = new_thread(callback, fd_sock);
		if (ret != 0)
			return -1;
	}
	return *fd_sock;
}

int 
accept(int fd, sockaddr_in *addr_info, void *callback)
{
	if (callback != NULL) {
		while (1) {
			int *fd_con = (int *)malloc(sizeof(int));
			*fd_con = fd;
			le_accept(fd_con);
			if (fd == -1) {
				return fd;
			}
			int ret = new_thread(callback, fd_con);
			if (ret != 0)
				return -1;
		}
	}

	*addr_info = le_accept(&fd);
	return fd;
}

int
connect(const char* ip, int port)
{
	return le_con(ip, port);
}

int
read_block_header(int fd_sock, BlockHeader *block_header)
{
	unsigned char *buff = (unsigned char *)malloc(bh_basic_len + bh_extended_len);
	int is_extended = 0;
	uint8_t mode = 0;
	uint8_t type = 0;
	uint8_t length = 0;
	int ret = recv(fd_sock, buff, bh_basic_len, MSG_WAITALL);
	if (ret < 0)
		return -1;

	if (*buff & 0x80) {
		ret = recv(fd_sock, buff + bh_basic_len, bh_extended_len, MSG_WAITALL);
		if (ret < 0)
			return -1;
		is_extended = 1;
	}

	mode = *buff >> 6;
	if (is_extended) {
		type = (*buff & 0x3F << 8) + *(buff + 1) ;
	} else {
		type = (*buff & 0x3F);
	}

	if (mode == 0 || mode == 2) {
		length = type_len(type);
	} else {
		length = (*(buff + is_extended + 1) << 8) + *(buff + 2 + is_extended);
	}
	if (length != type_len(type) && length == 0) {
		return -2;
	}

	block_header->is_extended = is_extended;
	block_header->mode = mode;
	block_header->type = type;
	block_header->length = length;

	return 0;
}

size_t
read_block_body(int fd_sock, BlockHeader *block_header, void *buffer)
{
	return 0;
}

uint16_t
type_len(uint16_t type)
{
	return 0;
}

void
struct_register(const char *id, const char *member_length)
{

}


