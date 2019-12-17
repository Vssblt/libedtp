#ifndef BASE64_H
#define BASE64_H

#include <common.h>

typedef struct Base64 Base64;

struct Base64 {
	const char *table;
	const char *safeTable;
};

static Base64 base64 = { .table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", .safeTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};

size_t base64_encode(const u_char *str, size_t in_size, char *out);
size_t base64_decode(const u_char *str, size_t in_size, char *out);

size_t base64_safe_decode(const u_char *str, size_t in_size, char *out);
size_t base64_safe_encode(const u_char *str, size_t in_size, char *out);

#endif
