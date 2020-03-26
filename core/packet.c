#include "packet.h"
#include "socket.h"
#include "thread.h"
#include "common.h"
#include <malloc.h>
#include <string.h>

size_t read_sizeof(int fd_sock);

int
listen(int port, void *callback, int backlog)
{
	int fd_sock;
	fd_sock = le_listen(port, backlog);
	if (callback != NULL && fd_sock != -1) {
		int ret = new_thread(callback, &fd_sock, sizeof(fd_sock));
		if (ret != 0)
			return -1;
	}
	return fd_sock;
}

int 
accept(int fd_con, sockaddr_in *addr_info, void *callback)
{
	if (callback != NULL) {
		while (1) {
			le_accept(&fd_con);
			if (fd_con == -1) {
				return fd_con;
			}
			int ret = new_thread(callback, &fd_con, sizeof(fd_con));
			if (ret != 0)
				return -1;
		}
	}

	*addr_info = le_accept(&fd_con);
	return fd_con;
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
	if (ret < 0) {
		goto ERR_1;
	}

	if (*buff & 0x80) {
		ret = recv(fd_sock, buff + bh_basic_len, bh_extended_len, MSG_WAITALL);
		if (ret < 0) {
			goto ERR_1;
		}
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
		goto ERR_2;
	}

	block_header->is_extended = is_extended;
	block_header->mode = mode;
	block_header->type = type;
	block_header->length = length;

	free(buff);
	return 0;

ERR_1:
	free(buff);
	return -1;

ERR_2:
	free(buff);
	return -2;
}

size_t
read_block_body(int fd_sock, BlockHeader *block_header, void *buffer)
{
	return 0;
}

#if defined __linux__ || defined __CYGWIN__
uint16_t
type_len(uint16_t type)
{
	FILE *fd = 0;
	uint16_t size = 0;
	uint16_t temp = 0;
	lestring len;

	char *str_type = (char *)malloc(6);
	memset(str_type, 0, 6);
	int ret = sprintf(str_type, "%d", type);
	if (ret <= 0) {
		goto ERR_1;
	}
	len = map_value(&struct_id_len_map, str_type);
	free(str_type);

	if (len.str == NULL || len.size == 0) {
		goto ERR_2;
	}

	fd = open_memstream(&len.str, (size_t *)&len.size);
	ret = 1;
	while (ret) {
		ret = fscanf(fd, "%hu ", &temp);
		size += temp;
	}
	ret = fscanf(fd, "%hu", &temp);
	if (ret)
		size += temp;
	lestring_free(&len);
	
	return size;

ERR_1:
	free(str_type);
	return 0;

ERR_2:
	lestring_free(&len);
	return 0;
}
#endif

void
struct_register(const char *name, uint16_t id, const char *member_length)
{
	char *str_id = (char *)malloc(6);
	memset(str_id, 0, 6);
	int ret = sprintf(str_id, "%d", id);
	if (ret <= 0) {
		goto RET;
	}

	map_insert(&struct_id_len_map, str_id, member_length);
	map_insert(&struct_name_id_map, name, str_id);
	
RET:
	free(str_id);
}


