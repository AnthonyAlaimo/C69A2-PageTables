#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

//linked list to keep track of pages  
typedef struct linked_list{
	int frame;
	struct linked_list *next_node;
	struct linked_list *prev_node;
}node;

node *head;
node *tail;
/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	// int toEvict;
	// node *curr = head;
	// node *prev =  NULL;
	// //vframe = head->frame
	// // SIZE = 0
	// if (head == NULL){
	// 	// do something
	// 	perror("No head");
	// }
	// // Size == 1
	// if(curr-> next_node == NULL){
	// 	head = NULL;
	// 	toEvict = curr->frame;
	// 	free(curr);
	// 	return toEvict;
	// } 
	// // Size > 1
	// while (curr->next_node != NULL){
	// 	prev = curr;
	// 	curr = curr->next_node;
	// }
	// prev->next_node = NULL; 
	// toEvict = curr->frame;
	// free(curr);
	// return toEvict;
	int toEvict;
	if (tail == NULL){
		// do something
		if (head == NULL){
			perror("No nodes");
			exit(1);
		}
		toEvict = head->frame;
		free(head);
		return toEvict;
		
	}
	node *evictTail = tail;
	tail = evictTail->prev_node;
	tail->next_node = NULL;
	toEvict = evictTail->frame;
	free(evictTail);
	return(toEvict);

}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	node *curr = head;

	while (curr != NULL){
		if (curr->frame == p->frame){
			return;
		}
		else{
			curr = curr->next_node;
		}
	}

	int f = p->frame;
	node *new = (node*)malloc(sizeof(node));
	new->frame = f;
	new->next_node = head;
	head->prev_node = new;
	new->prev_node = NULL;
	head = new;
	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	head = NULL;
	tail = NULL;
}
