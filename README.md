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
    ./run.sh gdb # good for testing multithread

## Implementation
### Process



### Features
- Additional malloc library functions Calloc and Reallocf # allowing compatibility with most commands
- Defragmentation of memory heaps to reduce munmap calls and improve performance # see free.c,
- Multi thread safe # use of mutex at all entry points

## Takeaways
- Purpose of malloc:  
```c
#include <sys/mann.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
```
mmap() is a system call that returns the starting address of a memory region of size len. However system calls are time consuming, and processes can request memory very frequently. This is where malloc() comes in. By using mmap() to preallocate heaps dedicated to memory allocations of different sizes, and dividing these heaps into blocks to be returned by malloc, performance is greatly improved.
- Importance of memory alignment:  
Because of the way processors access memory (one word at a time, where word size depends on the processor), if the structures and memory ranges that make up mmap heaps are not perfectly aligned (relative to processor word size) some processes that make large numbers of allocations can cause memory corruption to occur.
Simple padding on input size and structure size to align on 16 bytes can help prevent this issue.
```c
malloc_size = (size + 15) & ~15;
```

## Useful links
C dynamic memory allocation https://en.wikipedia.org/wiki/C_dynamic_memory_allocation  
Malloc and memory alignment https://stackoverflow.com/questions/8575822/which-guarantees-does-malloc-make-about-memory-alignment#8575954  
