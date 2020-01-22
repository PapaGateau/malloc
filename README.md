# Malloc
C implementation of the malloc library using mmap and munmap.  
This project is a great introduction memory management and dynamic memory allocation.

## Functions
```c
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void *reallocf(void *ptr, size_t size);
void *calloc(size_t count, size_t size);
void show_alloc_mem(void);
```

## Commands
### Build
From root directory:
```bash
make
make clean
make fclean
```
### Testing
Building this project creates a shared library ```libft_malloc.so```  
Using the run.sh we can run any command and force it to use our library:
```bash
./run.sh ls -l # uses obscure malloc and realloc behaviour
./run.sh vim # makes a large number of allocations and uses calloc
./run.sh gdb # good for testing multithread
```
## Implementation
### Process
First we allocate a memory range using mmap()
```c
#include <sys/mann.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
```
```c
typedef struct        s_range
{
	char               padding[12];
	enum e_range_type  type;
	size_t             space;
	struct s_range     *next;
}                     t_range;
```
For better performance, these ranges are used as heaps for allocations of different sizes. These heaps are defined by three different types: TINY, SMALL and LARGE
```c
# define TINY_MAX_BLOCK_SIZE 128
# define TINY_RANGE_SIZE (4 * getpagesize())
# define SMALL_MAX_BLOCK_SIZE 1024
# define SMALL_RANGE_SIZE (32 * getpagesize())
```
The TINY and SMALL heaps are divided into blocks, that will will represent individual malloc calls
```c
typedef struct			s_block
{
	char				padding[12];
	t_bool				freed;
	size_t				size;
	struct s_block		*next;
}						t_block;
```
LARGE ranges, for malloc calls of size > SMALL_BLOCK_SIZE will only contain one block

### Features
- Additional malloc library functions Calloc and Reallocf, allowing compatibility with most commands
- Defragmentation of memory heaps to reduce munmap calls and improve performance (see free.c)
- Multi thread safe (use of mutex at all entry points)

## Takeaways
- Purpose of malloc:  
mmap() is a system call that returns the starting address of a memory region of size len. However system calls are time consuming, and processes can request memory very frequently. This is where malloc() comes in. By using mmap() to preallocate heaps dedicated to memory allocations of different sizes, and dividing these heaps into blocks to be returned by malloc, performance is greatly improved.

- Importance of memory alignment:  
Because of the way processors access memory (one word at a time, where word size depends on the processor), if the structures and memory ranges that make up mmap heaps are not perfectly aligned (relative to processor word size) some processes that make large numbers of allocations can cause memory corruption to occur.
Simple padding on input size and structure size to align on 16 bytes can help prevent this issue.
```c
malloc_size = (size + 15) & ~15;
```

## Useful links
[C dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)  
[Malloc and memory alignment](https://stackoverflow.com/questions/8575822/which-guarantees-does-malloc-make-about-memory-alignment#8575954)
