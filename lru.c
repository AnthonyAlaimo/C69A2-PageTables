#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int ref_count;
//linked list to keep track of pages  
// typedef struct linked_list{
// 	int frame;
// 	struct linked_list *next_node;
// 	struct linked_list *prev_node;
// }node;

// node *head;
// node *tail;
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
	// int toEvict;
	// if (tail == NULL){
	// 	// do something
	// 	if (head == NULL){
	// 		perror("No nodes");
	// 		exit(1);
	// 	}
	// 	toEvict = head->frame;
	// 	free(head);
	// 	return toEvict;
		
	// }
	// node *evictTail = tail;
	// tail = evictTail->prev_node;
	// tail->next_node = NULL;
	// toEvict = evictTail->frame;
	// free(evictTail);
	// return(toEvict);

    int min_ref= coremap[0].pte->ref_count;;
    int output= 0;
    int i = 0;
    while(i<memsize){
    	if(i > 0 && coremap[i].pte->ref_count <min_ref){
    		min_ref = coremap[i].pte->ref_count;
    		output = i;
    	}
    	i += 1;
    }
    return output;



}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	// node *curr = head;

	// while (curr != NULL){
	// 	if (curr->frame == p->frame){
	// 		return;
	// 	}
	// 	else{
	// 		curr = curr->next_node;
	// 	}
	// }


	// int f = p->frame;
	// node *new = (node*)malloc(sizeof(node));
	// new->frame = f;
	// new->next_node = head;
	// if (head==NULL){
	// 	;
	// }
	// else {
	// 	head->prev_node = new;
	// }
	// new->prev_node = NULL;
	// head = new;
	// return;

	p->ref_count = ref_count;
	ref_count += 1; 
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	//head = NULL;
	//tail = NULL;
	ref_count = 0;
}
