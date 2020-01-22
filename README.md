# Malloc
C implementation of the malloc library using mmap and munmap.  
This project is a great introduction memory management and dynamic memory allocation.

## Functions
```c
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					*reallocf(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);
void					show_alloc_mem(void);
```

## Commands
### Build
From root directory:

    make
    make clean
    make fclean

### Testing
Building this project creates a shared library ```libft_malloc.so```  
Using the run.sh we can run any command and force it to use our library:

    ./run.sh ls
    ./run.sh vim
    ./run.sh gdb

## Implementation
### Process

```c
#include <sys/mann.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
```

mmap() is a system call that returns the starting address of a memory region of size len.  
However system calls are time consuming, and processes can request memory very frequently.  This is where malloc() comes in. By using mmap() to allocate heaps dedicated to memory allocations of different sizes, and dividing these heaps into blocks to be returned by malloc, performance is greatly improved.

### Features
defragmentation
multi thread safe
inclusion of additional malloc library functions (calloc reallocf)

## Takeaways
purpose of malloc (reducing expensive system calls by preallocating memory)
importance of memory alignment (memory corruption)

## Useful links
C dynamic memory allocation https://en.wikipedia.org/wiki/C_dynamic_memory_allocation
Malloc and memory alignment https://stackoverflow.com/questions/8575822/which-guarantees-does-malloc-make-about-memory-alignment#8575954
