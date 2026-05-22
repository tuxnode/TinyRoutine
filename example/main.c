#include "uthread.h"
#include <stdio.h>

void foo(void)
{
	for (int i = 0; i < 5; i++) {
		printf("  [foo] iteration %d\n", i);
		uthread_yield();
	}
	printf("  [foo] done\n");
}

void bar(void)
{
	for (int i = 0; i < 3; i++) {
		printf("  [bar] iteration %d\n", i);
		uthread_yield();
	}
	printf("  [bar] done\n");
}

int main(void)
{
	int t0 = uthread_creat(foo);
	int t1 = uthread_creat(bar);

	printf("[main] created thread %d and %d, starting scheduler\n", t0, t1);

	schedule();

	printf("[main] back to main, done\n");
	return 0;
}
