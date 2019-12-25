#include "thread.h"

void
new_thread(void *func, void *arg)
{
	if (arg != NULL) {
		func(arg);
	} else {
		func();
	}

}
