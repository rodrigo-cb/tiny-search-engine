/* 
 * index.c - CS50 'index' module
 *
 * see index.h for more information.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "index.h"
#include "memory.h"
#include "jhash.h"
#include "set.h"
#include "file.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct indexnode {
  counters_t *item;		      // pointer to data for this item
  const char *key;              // string key to this item
  struct indexnode *next;	      // link to next node
} indexnode_t;

/**************** global types ****************/
typedef struct hashtable_t {
  set_t **array;	      // array of pointers to sets
  int size;
} index_t;

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */
// static void ctrs_print(FILE *fp, const char *key, void *item);
static void ctrs_print(void *arg, const char *key, void *item);
static void ctrs_delete(void *ctrs);
static void ctrs_save(void *arg, const char *key, void *item);
static void num_save(void *arg, const int key, int count);

/**************** index_new() ****************/
index_t *index_new(const int num_slots)
{
    return (index_t*)hashtable_new(num_slots);
}

/**************** index_insert() ****************/
    bool index_insert(index_t *idx, const char *key, counters_t *item)
    {
        return hashtable_insert((hashtable_t*)idx, key, item);
    }
/**************** index_find() ****************/
    counters_t *index_find(index_t *idx, const char *key){
        return hashtable_find((hashtable_t*)idx, key);
    }

/**************** index_print() ****************/
    void index_print(index_t *idx, FILE *fp)
    {
        if (fp == NULL){
            return;
        }
        if (idx == NULL){
            printf("(null)");
            return;
        }
        index_iterate(idx, fp, ctrs_print);
    }

/**************** index_iterate() ****************/
    void index_iterate(index_t *idx, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) )
    {
        hashtable_iterate((hashtable_t*)idx, arg, itemfunc);
    }

    /**************** index_delete() ****************/
    void index_delete(index_t *idx)
    {
        if (idx != NULL) {
            for (int i = 0; i < idx->size; i++){
                set_delete(idx->array[i], ctrs_delete);
            }
            count_free(idx->array);
            count_free(idx);
        }
        #ifdef MEMTEST
            count_report(stdout, "End of index_delete");
        #endif
    }

    /**************** index_save() ****************/

    void index_save(index_t *idx, char *filename)
    {
        FILE *fp = fopen(filename, "w");
        if (fp == NULL){
            fprintf(stderr,"file doesn't exist of is not writeable");
            return;
        }
        index_iterate(idx, fp, ctrs_save);
        fclose(fp);
    }

    /**************** index_load() ****************/

    index_t *index_load(char *filename)
    {
        FILE *fp = fopen(filename, "r");
        if (fp == NULL){
            fprintf(stderr,"file doesn't exist of is not readable");
            return NULL;
        }

        index_t *idx = index_new(lines_in_file(fp));

        char * word = readwordp(fp);
        while (word != NULL) {
            int key;
            int count;
            counters_t *ctrs = counters_new();
            index_insert(idx, word, ctrs);
            while ( fscanf(fp, "%d %d", &key, &count) == 2){
                counters_set(ctrs, key, count);
            }
            free(word);
            word = readwordp(fp);
        }
        fclose(fp);
        return idx;
    }

      /****************ctrs_print() ****************/
    //Helper function that prints a counters item
    static void ctrs_print(void *arg, const char *key, void *item)
    {
        counters_t* ctrs = item;
        FILE *fp = arg;
        if (ctrs != NULL) {
            fprintf(fp, "%s: ", key);
            counters_print(ctrs, fp);
        }
    }

     /****************ctrs_save() ****************/
    //Helper function to save a counters item to a file
    static void ctrs_save(void *arg, const char *key, void *item)
    {   
        FILE *fp = arg;
        counters_t* ctrs = item;
        if (ctrs != NULL) {
            fprintf(fp, "%s ", key);
            counters_iterate(ctrs, fp, num_save);
            fprintf(fp, "\n");
        }
    }

    /****************num_save() ****************/
    //Helper function to save a counters key and count to a file
    static void num_save(void *arg, const int key, int count)
    {   
        FILE *fp = arg;
        fprintf(fp, "%d %d ", key, count);
    }

     /****************ctrs_delete() ****************/
    //Helper function that deletes a counters item
    static void ctrs_delete(void *ctrs)
    {
        //counters_t *ct = ctrs;
        counters_delete((counters_t*)ctrs);
    }