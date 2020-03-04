#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"
#include "sim.h"



extern int debug;

extern struct frame *coremap;

  
typedef struct linked_list{
	addr_t address;
	struct linked_list *next_node;
}node;

node *head;

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	int i=0;
	int output = -1;
	int max = -1;
	int found;
	int address_cell;
	int j;
	// loops through to find when the current nodes address is equal to the coremap address 
	while(i < memsize) {
			found = 0;
			j = 0;
			address_cell = 0;
			node *curr = head;
			while (curr != NULL) {
				// if found we exit the loop and store it in address_cell
				if (curr->address == coremap[i].address) {
					address_cell = j;
					found = 1;
					break;
				}
				j++;
				curr = curr->next_node;
			}
			// if not found return i
			if (found == 0) {
				return i;
			} else if (address_cell > max) {
				output = i;
				max = address_cell;
			}
			i++;
	}

	return output;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {
	// removes the head of the list
	node *cur = head;
	node *new_head = cur->next_node;
	head = new_head;
	free(cur);
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	// code used from the sim.c program, used to read the trace files
	char buf[MAXLINE];
	addr_t vaddr = 0;
	char type;
	FILE* trace_file;
	// opens attepmt to read the file, if fails throw a p error
	if(!(trace_file = fopen(tracefile, "r"))) {
		perror("frace file does not exist");
		exit(1);
	}

	node *prev_node;
	while(fgets(buf, MAXLINE, trace_file) != NULL) {
		if(buf[0] != '=') {
			sscanf(buf, "%c %lx", &type, &vaddr);
			// allocates memeory for the new node
			node *new_trace = (node*) malloc(sizeof(node));
			new_trace->address = vaddr;
			new_trace->next_node = NULL;
			// if the head is null, we set the new node as the head
			if (head == NULL) {
				head = new_trace;
			} else {
				// otherwise, we add it to the list
				prev_node->next_node = new_trace;
			}
			prev_node = new_trace;
		} else {
			continue;
		}
	}

}

