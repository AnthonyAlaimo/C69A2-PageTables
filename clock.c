#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

int clock_position;

extern struct frame *coremap;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	for (clock_position = 0; clock_position < memsize; clock_position++){
		//check if the frame is referenced or not
		if (coremap[clock_position].pte->frame & PG_REF){
			//set reference to 0
			coremap[clock_position].pte->frame = coremap[clock_position].pte->frame & (~PG_REF);
		}else{
			//evict page
			return clock_position;

		}

	}
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	//not needed
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
	clock_position = 0;
}
