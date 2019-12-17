#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

typedef unsigned char u_char;

uint32_t timestamp();

//int random(int min, int max);

int is_little_endian();

uint32_t mhash(const char* str, uint32_t len);

void print_time();

//void mt_random(u_char *mem, unsigned int len);

void bin2hex(const u_char *data, uint32_t size, char *out);

//void uuid(char *_uuid);

#endif
