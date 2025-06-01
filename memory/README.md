# Memory Management in C

This directory contains programs demonstrating fundamental memory management concepts in C programming language.

## Programs

### 1. Stack Memory (stack.c)

This program demonstrates stack memory allocation through recursion:

- Shows how the stack grows with each recursive function call
- Displays memory addresses of local variables at different recursion levels
- Illustrates how stack frames are created and arranged in memory

To compile and run:

```bash
gcc -o stack stack.c
./stack
```

### 2. Heap Memory (heap.c)

This program demonstrates dynamic memory allocation using the heap:

- Shows allocation of memory using `malloc()`
- Demonstrates resizing allocated memory using `realloc()`
- Illustrates proper memory deallocation with `free()`
- Displays memory addresses of dynamically allocated arrays and their elements

To compile and run:

```bash
gcc -o heap heap.c
./heap
```

## Memory Concepts Illustrated

### Stack Memory

- Automatically allocated/deallocated
- Fixed size determined at compile time
- LIFO (Last In, First Out) structure
- Stores local variables, function parameters, return addresses
- Memory is contiguous and well-organized

### Heap Memory

- Manually allocated/deallocated by the programmer
- Dynamic size that can change at runtime
- Non-contiguous memory allocation
- Persists beyond the scope of functions
- Requires explicit management to prevent memory leaks

## Common Memory Issues

1. **Stack Overflow**: Occurs when too many recursive calls exhaust stack space
2. **Memory Leaks**: Happen when heap memory is allocated but never freed
3. **Dangling Pointers**: Result from accessing memory that has been freed
4. **Buffer Overflows**: Caused by writing beyond allocated memory bounds

These examples provide visual demonstrations of how memory is organized and managed in C programs.
