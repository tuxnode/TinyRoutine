#include <stdio.h>
#include <stdlib.h>

#include "../include/uthread.h"

TCB thread_table[MAX_THREADS];
int cur_id = -1; // -1代表主进程
context_t main_ctx;

void thread_entry()
{
	void (*func)(void);

	// 取出函数指针
	__asm__("movq %%rbx, %0" : "=r"(func));

	func();

	printf("[System] Thread %d finished execution.\n", cur_id);
	thread_table[cur_id].state = EXITED;

	schedule();
}

// 为线程分配独立的空间
int uthread_creat(void (*func)(void))
{
	int id = -1;
	for (int i = 0; i < MAX_THREADS; i++) {
		if (thread_table[i].state == FREE) {
			id = i;
			break;
		}
	}
	if (id == -1)
		return -1;

	TCB *t = &thread_table[id];
	t->id = id;
	free(t->stack);
	t->stack = malloc(STACK_SIZE);

	uint64_t *sp = (uint64_t *)(t->stack + STACK_SIZE);
	sp--;
	sp = (uint64_t *)((uintptr_t)sp & ~0xFUL); // 16字节对齐

	*sp = (uint64_t)thread_entry;

	t->ctx.rsp = (uint64_t)sp;
	t->ctx.rbp = (uint64_t)sp;
	t->ctx.rbx = (uint64_t)func;

	t->state = READY;
	return id;
}

void schedule()
{
	int next_id = -1;
	for (int i = 0; i < MAX_THREADS; i++) {
		int index = (cur_id + 1 + i) % MAX_THREADS;
		if (thread_table[index].state == READY) {
			next_id = index;
			break;
		}
	}

	if (next_id != -1) {
		int prev_id = cur_id;
		cur_id = next_id;
		thread_table[next_id].state = RUNNING;

		if (prev_id == -1) {
			ctx_switch(&main_ctx, &thread_table[next_id].ctx);
		} else {
			ctx_switch(&thread_table[prev_id].ctx,
				   &thread_table[next_id].ctx);
		}
	} else {
		if (cur_id != -1 && thread_table[cur_id].state == RUNNING) {
			return;
		}
		printf("[System] No more threads. Returning to main.\n");

		int prev_id = cur_id;
		cur_id = -1;
		if (prev_id != -1) {
			ctx_switch(&thread_table[prev_id].ctx, &main_ctx);
		}
	}
}

void uthread_yield()
{
	if (cur_id != -1) {
		thread_table[cur_id].state = READY;
		schedule();
	}
}
