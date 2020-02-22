#include "thread.h"
#if defined __linux__ || defined __CYGWIN__
#include <pthread.h>
#endif


#if defined __linux__ || defined __CYGWIN__

struct func_info{
	void *func;
	void *arg;
};

static void *thread1(void *);

int
new_thread(void *func, void *arg)
{
	pthread_t pt_t;
	func_info f = {func, arg};
	return pthread_create(&pt_t, NULL, thread1, &f);

}

void *
thread1(void *f)
{
	func_info *func = (func_info *)f;
	if (func->arg != NULL)
		((thread_func)func->func)(func->arg);
	else
		((thread_func_none_arg)func->func)();
	return NULL;
}
#endif


