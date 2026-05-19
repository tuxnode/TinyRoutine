#include <stdint.h>

typedef struct {
  uint64_t rsp;
  uint64_t rbp;
  uint64_t rbx;
  uint64_t r12;
  uint64_t r13;
  uint64_t r14;
  uint64_t r15;
}context_t;

#define STACK_SIZE (64 * 1024)

typedef enum {
  FREE,
  READY,
  RUNNING,
}ThreadState;

typedef struct {
  int id;
  context_t ctx;
  ThreadState state;
  char *stack;
} TCB;

// switch.S
// void ctx_switch(context_t *prev, context_t *next);
