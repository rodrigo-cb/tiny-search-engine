/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "counters.h"
#include "memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode {
  int key;
  int counter;
  struct countersnode *next;	      // link to next node
} countersnode_t;

/**************** global types ****************/
typedef struct counters {
  struct countersnode *head;	      // head of the list of items in counters
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t *countersnode_new(int key);

/**************** counters_new() ****************/
counters_t* counters_new(void)
{
  counters_t *counters = count_malloc(sizeof(counters_t));

  if (counters == NULL) {
    return NULL; // error allocating counters
  } else {
    // initialize contents of counters structure
    counters->head = NULL;
    return counters;
  }
}

/**************** counters_add() ****************/
int counters_add(counters_t *ctrs, const int key)
{

  if (ctrs != NULL && key > 0) {
    // Check if key is already contained in the counters
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next){
        if (node->key == key){
            node->counter ++;
            return node->counter;
        }
    }
    // allocate a new node to be added to the list
    countersnode_t *new = countersnode_new(key);
    
    if (new != NULL) {
      // add it to the head of the list
      new->counter = 1;
      new->next = ctrs->head;
      ctrs->head = new;
      return 1;
    }
  }
  return 0;

#ifdef MEMTEST
  count_report(stdout, "After counters_insert");
#endif
}

/**************** countersnode_new ****************/
/* Allocate and initialize a countersnode */
// the 'static' modifier means this function is not visible 
// outside this file
static countersnode_t* countersnode_new(int key)
{
  countersnode_t *node = count_malloc(sizeof(countersnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key = key;
    node->next = NULL;
    node->counter = 0;
    return node;
  }
}

/**************** counters_get() ****************/
int counters_get(counters_t *ctrs, const int key)
{
  if (ctrs == NULL) {
    return 0; // bad counters
  } 
  else {
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key){
            return node->counter;
        }
    }
    return 0;
  }
}

/**************** counters_set() ****************/
void counters_set(counters_t *ctrs, const int key, int count)
{
    if (ctrs != NULL && key > 0 && count > 0){
        for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key){
                node->counter = count;
                return;
            }
        }
        // allocate a new node to be added to the list
        countersnode_t *new = countersnode_new(key);
        if (new != NULL) {
            // add it to the head of the list
            new->counter = count;
            new->next = ctrs->head;
            ctrs->head = new;
        }
    }
}
/**************** counters_print() ****************/
void counters_print(counters_t *ctrs, FILE *fp)
{
    if (fp != NULL) {
    if (ctrs != NULL) {
      fputc('{', fp);
      for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
        // print this node
        fputc(' ', fp);
        fprintf(fp, "%d:%d ", node->key, node->counter); 
      }
      fputs(" }\n", fp);
    } else {
      fputs("(null)", fp);
    }
  }
}

/**************** counters_iterate() ****************/

void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->counter); 
    }
  }
}

/**************** counters_delete() ****************/
void counters_delete(counters_t *ctrs)
{
  if (ctrs != NULL) {
  for (countersnode_t *node = ctrs->head; node != NULL; ) {
    countersnode_t *next = node->next;	    // remember what comes next
    free(node);			    // free the node
    node = next;			    // and move on to next
  }
  free(ctrs);
}

#ifdef MEMTEST
    count_report(stdout, "End of counters_delete");
#endif
}