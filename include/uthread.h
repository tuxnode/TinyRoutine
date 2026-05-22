#ifndef UTHREAD_H
#define UTHREAD_H

#include <stdint.h>

#define STACK_SIZE (64 * 1024)
#define MAX_THREADS 4

typedef struct {
	uint64_t rsp;
	uint64_t rbp;
	uint64_t rbx;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
} context_t;

typedef enum {
	FREE,
	READY,
	RUNNING,
	EXITED,
} ThreadState;

typedef struct {
	int id;
	context_t ctx;
	ThreadState state;
	char *stack;
} TCB;

// switch.S
extern void ctx_switch(context_t *prev, context_t *next);
void thread_entry();
void schedule();
int uthread_creat(void (*func)(void));
void uthread_yield();

#endif
