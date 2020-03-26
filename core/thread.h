#ifndef LIBEDTP_THREAD_H
#define LIBEDTP_THREAD_H
#include <stddef.h>

int new_thread(const void *func, const void *arg, size_t size);
typedef void (*thread_func)(void *arg);
typedef void (*thread_func_none_arg)();

#endif
