#include "thread.h"

void
new_thread(void *func, void *arg)
{
	if (arg != NULL) {
		((thread_func)func)(arg);
	} else {
		((thread_func_none_arg)func)();
	}

}
