/* 
 * indexer.c - CS50 'indexer' program
 * Reads files from crawler-produced directory and writes an index into a file.
 * Indexes from words to (PageID : count) pairs
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "bag.h"
#include "counters.h"
#include "pagedir.h"
#include "hashtable.h"
#include "index.h"
#include "word.h"
#include "memory.h"

// Constants
int NUM_SLOTS = 600;

// Function Prototypes
int check_input(int argc, char *argv[]);
void print_webpage(FILE *fp, void *item);
void build_index (char * dirname, index_t *idx);
void index_word(char *word, index_t *idx, webpage_t *page);

int main(int argc, char *argv[]) 
{
    char *dirname = argv[1];
    char *filename = argv[2];
    int error_code;
    if ( (error_code = check_input(argc, argv)) != 0){
        return error_code;
    }
    // Initialize index
    index_t *index = assertp(index_new(NUM_SLOTS), "Error initializing index");

    // Fill index based on files in dirname     
    build_index(dirname, index);

    // Save index to given filename
    index_save(index, filename);

    // Cleanup
    index_delete(index);

    return 0;
}

void build_index (char * dirname, index_t *idx){

    // Create and fill bag with webpages from dirname
    bag_t *p_bag = assertp(bag_new(), "Error initializing bag");
    read_from_dir(dirname, p_bag);

    //loop through all webpages
    webpage_t *page;
    while ( (page = bag_extract(p_bag)) != NULL){
        int pos = 0;
        char *word;

        // loop through all words in the webpage
        while ( ( pos = webpage_getNextWord(page, pos, &word) ) != -1){
            // Index each word and PageID it was found on
            index_word(word, idx, page);
        }
        webpage_delete(page);
    }
    // Cleanup
    bag_delete(p_bag, webpage_delete);
}

int check_input(int argc, char *argv[])
{
    //Check for correct number of parameters
    if (argc != 3){
        fprintf(stderr, "Usage: ./indexer pageDirectory indexFilename\n");
        return 1;
    }
    //Validate directory name
    if ( ! isCrawlerDirectory(argv[1])){
        fprintf(stderr, "pageDirectory is not an existing directory produced by the crawler\n");
        return 2;
    }
    //Validate file name
    FILE *fp; 
    fp = fopen(argv[2], "w");
    if (fp == NULL){
        fprintf(stderr, "indexFilename is not a writeable file\n");
        return 3;
    }
    fclose(fp);
    return 0;
}

void index_word (char * word, index_t *idx, webpage_t *page)
{
    // ignore words that are less than 3 characters 
    if (strlen(word) < 3) { 
        free(word);
        return;
    }
    // normalize word
    make_lower_case(&word);

    // Create or find the counters corresponding to the word
    counters_t *ctrs;
    if ( ( ctrs = index_find(idx, word)) == NULL){
        index_insert (idx, word, counters_new());
    }
    ctrs = index_find(idx, word);

    // Add the Webpage's ID to the counters object for the word
    counters_add(ctrs, webpage_getDepth(page)); // The ID was saved in the webpage's depth field

    //Cleanup
    free (word);
}