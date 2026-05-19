.intel_syntax noprefix

.global ctx_switch
.text
.align 8

// void ctx_switch(context_t *prev, context_t *next);
// rdi -> prev
// rsi -> next
ctx_switch:
  mov [rdi], rsp
  mov [rdi + 8], rbp
  mov [rdi + 16], rbx
  mov [rdi + 24], r12
  mov [rdi + 32], r13
  mov [rdi + 40], r14
  mov [rdi + 48], r15

  mov rsp, [rsi]
  mov rbp, [rsi + 8]
  mov rbx, [rsi + 16]
  mov r12, [rsi + 24]
  mov r13, [rsi + 32]
  mov r14, [rsi + 40]
  mov r15, [rsi + 48]

  ret
