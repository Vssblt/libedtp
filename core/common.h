#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

enum {
	COPY,
	COPY_AND_NEW,
};

#ifdef __GNUC__
#define max(x, y) ({ \
	typeof(x) _max1 = (x); \
	typeof(y) _max2 = (y); \
	(void)(&_max1 == &_max2); \
	_max1 > _max2 ? _max1 :_max2; \
})
#else
#define max(x, y) ({ \
	x > y ? x : y; \
})
#endif

typedef struct lestring {
	char *str;
	int size;
}lestring;

typedef unsigned char u_char;

static int edtp_type[65536] = {0};

uint32_t timestamp();

int random_s(int min, int max, int *err);

int is_little_endian();

uint32_t mhash(const char* str, uint32_t len);

void print_time();

int random_mem(u_char *mem, uint32_t len);

void bin2hex(const u_char *data, uint32_t size, char *out);

void uuid(char *_uuid);

void lestring_copy(lestring dst, lestring srt);

#endif
