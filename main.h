// virtual address space - 1. text section: binary instructions to be executed
// 						   2. data section: contains non-zero initialized static data
// 						   3. BSS (block started by symbol): zero initialized static data
// 						   4. heap: contains the dynamically allocated data
// 						   5. stack: contains your automatic variables, function arguments, copy of based pointer..
// 
// stack and heap grow in opposite directions
// data, bss, heap are usually called "data segment", the end of which is demarcated by program break (brk) pointer
// brk points to the end of the heap
// when allocating memory, we request the system to increment brk
// when releasing memory, we request the system to decrement brk
// 
// on unix based system, we make use of sbrk()
// sbrk(0) - current address of the program break
// sbrk(x), x > 0 increments brk by x bytes -> allocating memory
// sbrk(x), x < 0 decrements brk by x bytes -> releasing memory
// on failure, sbrk returns (void *) -1
// 
// gotta look at mmap() too

#include <stdbool.h>
#include <stdio.h>

typedef char ALIGN[16];

union mblock {
	typedef struct {
		size_t size;
		bool is_free;
		struct mblock *next;
	}  mblock;

	ALIGN stub; // ensures 16 bytes alignment 
}

typedef union mblock mblock_t;

void *malloc(size_t size);
mblock_t *get_free_block(size_t size);
