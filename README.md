# Malloc
C implementation of the malloc library using mmap and munmap.  

## Functions
```c
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					*reallocf(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);
void					show_alloc_mem(void);
```

## Build commands
from malloc directory:
    make
    make clean
    make fclean

## Use
Building this project creates a shared library ```libft_malloc.so```  
Using the run.sh script we can force the use of this library:  
```
    ./run.sh ls
    ./run.sh vim
    ./run.sh gdb
```
## Process
```c
#include <sys/mann.h>
void mmap(void addr, size_t len, int prot, int flags, int fd, off_t offset);
```

mmap() is a system call that allows us to allocate memory ranges of size len.
However system calls are time consuming, and programs tend to allocate and deallocate memory often

## Features

## Takeaways
importance of memory alignment
