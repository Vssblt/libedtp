#include "thread.h"
#if defined __linux__ || defined __CYGWIN__
#include <pthread.h>
#endif
#include <malloc.h>
#include <string.h>


#if defined __linux__ || defined __CYGWIN__

struct func_info{
	const void *func;
	void *arg;
};

static void *thread1(void *);

int
new_thread(const void *func, const void *arg, size_t arg_size)
{
	pthread_t pt_t;
	func_info *f = (func_info *)malloc(sizeof(func_info));
	f->func = func;
	if (arg != NULL) {
		f->arg = (void *)malloc(arg_size);
		memcpy(f->arg, arg, arg_size);
	} else {
		f->arg = NULL;
	}
	int ret = pthread_create(&pt_t, NULL, thread1, f);
	if (ret != 0) {
		free(f->arg);
		free(f);
	}
	
	return ret;
}

void *
thread1(void *f)
{
	func_info *func = (func_info *)f;
	if (func->arg != NULL)
		((thread_func)func->func)(func->arg);
	else
		((thread_func_none_arg)func->func)();
	free(f);
	return NULL;
}
#endif


