#ifndef LIBEDTP_PACKET_H
#define LIBEDTP_PACKET_H
#include <stddef.h>
#include <netinet/in.h>
#include "map.h"

static int bh_basic_len = 1;
static int bh_extended_len = 1;

static EdtpMap struct_name_id_map;
static EdtpMap struct_id_len_map;

struct StreamHeader {
	uint16_t block_count;
	uint8_t version;
	uint16_t current_block;
};

struct BlockHeader {
	int is_extended;
	uint8_t mode;
	uint16_t type;
	uint16_t length;
};

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

int read_stream_head(int fd_sock, StreamHeader *info);

size_t read_block_header(int fd_sock, StreamHeader *header_info, void *buff, size_t max_size = -1);

size_t read_block_body(int fd_sock, BlockHeader *block_header, void *buffer);

void struct_register(const char *name, uint16_t id, const char *member_length);

uint16_t type_len(uint16_t type);

#endif

