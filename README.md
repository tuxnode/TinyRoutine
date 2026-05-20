# TinyRoutine

一个仅 ~200 行的微型用户态协程库，用 C 和 x86-64 汇编从零实现，用于学习协作式多任务与上下文切换原理。

## 快速开始

```bash
make run
```

## 概述

- 纯用户态协作式调度，不依赖操作系统
- 汇编实现 `ctx_switch`，手动保存/恢复寄存器（`rsp`, `rbp`, `rbx`, `r12`–`r15`）
- 最多 4 个线程，每个 64 KB 栈
- 通过 `uthread_creat()` 创建，`uthread_yield()` 主动让出 CPU
- 轮询调度器

## 许可证

MIT
