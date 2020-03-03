#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

extern int oldest;

int fifo_evict() {
	// Set oldest element to evict
	int toEvict = oldest;
	int next_oldest;
	if (oldest == memsize-1){
		next_oldest = 0;
	}
	else {
		next_oldest = oldest + 1;
	}
	// Set next oldest to current oldest (now that we've evicted the oldest)
	oldest = next_oldest;
	// Return eviction index
	return toEvict;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {

	return;
	
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	oldest = 0;
}
