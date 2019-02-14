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
#include "index.h"
#include "word.h"


/**************** local types ****************/
// typedef struct page_and_id {
//   webpage_t *page;	      // pointer to webpage
//   int id;                 // id num
// } page_and_id_t;

// Constants
int NUM_SLOTS = 50;

// Function Prototypes
int check_input(int argc, char *argv[]);
void print_webpage(FILE *fp, void *item);

int main(int argc, char *argv[]) 
{
    char *dirname = argv[1];
    char *filename = argv[2];
    int error_code;
    if ( (error_code = check_input(argc, argv)) != 0){
        return error_code;
    }
    //index();
    //build index (ht)
    index_t *index = index_new(NUM_SLOTS);

    // put all webpages in a bag
    // Loop through all webpages in bag
    //  Loop through all words in webpage
    //   if !(ht_insert(word, new counters)){
            //ht_get(word).add(webpage_name)
    //}
    
    bag_t *p_bag = bag_new();
    read_from_dir(dirname, p_bag);
    //bag_print(p_bag, stdout, print_webpage);
    //loop through all webpages
    webpage_t *page; //= bag_extract(p_bag);
    while ( (page = bag_extract(p_bag)) != NULL){
        int pos = 0;
        char *word;
        // loop through all words in the webpage
        // Add word and pageID it was found on to index
        while ( ( pos = webpage_getNextWord(page, pos, &word) ) != -1){
            if (strlen(word) < 3) { // ignore words that are less than 3 characters 
                free(word);
                continue;
            }

            make_lower_case(&word);
            counters_t *ctrs;
            if ( ( ctrs = index_find(index, word)) == NULL){
                index_insert (index, word, counters_new());
            }
            ctrs = index_find(index, word);
            counters_add(ctrs, webpage_getDepth(page)); // webpage's depth field holds the ID
            free (word);
        }
        webpage_delete(page);
   }


    index_save(index, filename);
    // bag_t *p_bag = bag_new();
    // page_and_id_t *p_and_id;
    // while ( (p_and_id = bag_extract(p_bag)) != NULL){
    //     int pos = 0;
    //     char *word;
    //     while ( ( pos = webpage_getNextWord(p_and_id->page, pos, &word) ) != -1){
    //         hashtable_insert (index, word, counters_new());
    //         counters_t *ctrs = hashtable_find(index, word);
    //         counters_add(ctrs, p_and_id->id);
    //     }
    // }

    // Cleanup
    bag_delete(p_bag, webpage_delete);
    index_delete(index);

    return 0;
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

// print a name 
// void nameprint(FILE *fp, void *item)
// {
//   char *name = item; 
//   if (name == NULL) {
//     fprintf(fp, "(null)");
//   }
//   else {
//     fprintf(fp, "\"%s\"", name); 
//   }
// }

// void print_webpage(FILE *fp, void *item)
// {
//     webpage_t *page = item;
//     if (page == NULL){
//         fprintf(fp, "(null)");
//     } 
//     else {
//         fprintf(fp, "%s ", webpage_getURL(page)); 
//         fprintf(fp, "%d\n", webpage_getDepth(page)); 
//         fprintf(fp, "%s\n", webpage_getHTML(page));
//     } 
      
// }