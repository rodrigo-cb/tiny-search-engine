#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "pagedir.h"


// Function prototypes
int check_input(int argc, char *argv[]);
void crawl(char *argv[]);
void itemdelete(void* item);
void pagescanner(bag_t *bag, hashtable_t *ht, webpage_t *page);


int main(int argc, char *argv[]) 
{
    int error_code;
    if ( (error_code = check_input(argc, argv)) == 0){
        crawl(argv);
        return 0;
    }
    return error_code;
}

int check_input(int argc, char *argv[])
{
    //Check for correct number of parameters
    if (argc != 4){
        fprintf(stderr, "Usage: ./crawler seedURL pageDirectory maxDepth\n");
        return 1;
    }
    //Check if URL is valid
    if ( ! NormalizeURL(argv[1])){
        fprintf(stderr, "Error: Cannot normalize seed URL %s\n", argv[1]);
        return 2;
    }
    if (! IsInternalURL(argv[1])){
        fprintf(stderr, "Error: seed URL %s is not internal\n", argv[1]);
        return 3;
    }

    // Check if directory exists and is writable by trying to create a file there
    char *string = malloc(strlen(argv[2]) + 10);
    string[0] = '\0';    //start with clean string
    strcat(string, argv[2]);
    strcat(string, "/.crawler");
    FILE *fp = fopen(string, "w");
    free(string);
    if (fp == NULL){
        fprintf(stderr, "The directory doesn't exist or is not writable\n");
        return 4;
    }
    fclose(fp);

    //Check if maxdepth is valid
    int num = atoi(argv[3]);
    if ( (num == 0 && argv[3][0] != '0') || num < 0){
        fprintf(stderr, "maxDepth is not a valid number\n");
        return 5;
    }
    return 0;
}
void crawl(char *argv[])
{
    // variables
    char* seed_url = argv[1];
    char* dirname = argv[2];
    int max_depth = atoi(argv[3]);
    const int HT_SIZE = 150;
    
    //initialize structures
    hashtable_t *ht = hashtable_new(HT_SIZE);
    bag_t *bag = bag_new();

    //Check_input already made sure it's internal, so we just add seedURL to the bag
    webpage_t *seed_page = webpage_new(seed_url, 0, NULL);
    bag_insert(bag, seed_page);
    int page_id = 1; // counter for number of pages retrieved

    //loop through bag of URLs to visit
    webpage_t *webpage;
    while ( (webpage = bag_extract(bag)) != NULL){
        if (webpage_fetch(webpage)){
            write_to_dir(dirname, webpage, page_id); //create and write a file in dirname
            page_id ++;
            if (webpage_getDepth(webpage) < max_depth){
                pagescanner(bag, ht, webpage); //This scans and adds new URLs to Hashtable and Webpages to the bag,
            }
        }
        else {
            // If webpage_fetch returns False
            fprintf(stderr, "failed to fetch webpage %s\n", webpage_getURL(webpage));
        }
        webpage_delete(webpage);
    }
    hashtable_delete(ht, itemdelete);
    bag_delete(bag, itemdelete);

    // If at least one page was written
    if (page_id > 1) printf("Done writing webpage files into %s/\n", dirname);
}

/* Deletes a generic item
*/
void itemdelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}

/* Finds URLs that are linked to in the given webpage and, if they're valid, adds them to the hashtable, as well as creating 
and adding the corresponding webpage_t struct to the bag.
*/
void pagescanner(bag_t *bag, hashtable_t *ht, webpage_t *page)
{
    int pos = 0;
    char *result;
 
    while ((pos = webpage_getNextURL(page, pos, &result)) > 0) {
        if ( NormalizeURL(result)){
            if (IsInternalURL(result)){
                printf("Found url: %s\n", result);
                // Dummy item required in order to insert into hashtable.
                char* item = malloc(sizeof(char) *5);
                strcpy(item, "item");
                if (hashtable_insert(ht, result, item)){
                    // If URL not already in hashtable, add to hashtable and add webpage struct to bag
                    webpage_t *new_page = webpage_new(result, webpage_getDepth(page) +1, NULL);
                    bag_insert(bag, new_page);
                } else {
                    free(item);
                }
                
            }
            else {
                // If Non-internal URL
                fprintf(stderr, "Ignored non-internal URL %s\n", result);
            }
        } else {
            // If NormalizeURL returns false
            fprintf(stderr, "URL %s cannot be normalized\n", result);
        }
        free(result);
    }
}