#ifndef LIBEDTP_THREAD_H
#define LIBEDTP_THREAD_H
#include <stddef.h>

int new_thread(void *func, void *arg);
typedef void (*thread_func)(void *arg);
typedef void (*thread_func_none_arg)();

#endif
