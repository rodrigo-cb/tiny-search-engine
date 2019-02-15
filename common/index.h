#include <stdbool.h>
#include <stdio.h>
#include "counters.h"
#include "hashtable.h"

#ifndef __index_H
#define __index_H

/**************** global types ****************/
typedef struct hashtable_t index_t;  // opaque to users of the module, users do not know and cannot access members of this struct

/**************** functions ****************/

/* Create a new (empty) index; return NULL if error. */
index_t *index_new(const int num_slots);

/* Insert item, identified by key (string), into the given index.
 * The key string is copied for use by the index.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool index_insert(index_t *ht, const char *key, counters_t *item);

/* Return the item associated with the given key;
 * return NULL if index is NULL, key is NULL, key is not found.
 */
counters_t *index_find(index_t *ht, const char *key);

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void index_print(index_t *ht, FILE *fp);

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void index_iterate(index_t *idx, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole index; ignore NULL ht.
 */
void index_delete(index_t *ht);

/* Save the index into a file
 */
void index_save(index_t *idx, char *filename);


/* Load index from file
 */
index_t *index_load(char *filename);

#endif 