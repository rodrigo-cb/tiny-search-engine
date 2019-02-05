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
        fprintf(stderr, "Error: Cannot normalize seed URL\n");
        return 2;
    }

    // Check if directory exists and is writable by trying to create a file there
    char *string = malloc(strlen(argv[2]) + 10);
    // if (string == NULL) {
    //     fprintf(stderr, "Error allocating memory with malloc\n");
    //     return 3;
    // }
    string[0] = '\0';    //start with clean string
    strcat(string, argv[2]);
    strcat(string, "/.crawler");
    FILE *fp = fopen(string, "w");
    //printf("%s\n", string);
    free(string);
    if (fp == NULL){
        fprintf(stderr, "The directory doesn't exist or is not writable\n");
        return 3;
    }
    fclose(fp);

    //Check if maxdepth is valid
    int num = atoi(argv[3]);
    if (num == 0 && argv[3][0] != '0'){
        fprintf(stderr, "maxDepth is not a valid number\n");
        return 4;
    }
    return 0;
}
void crawl(char *argv[])
{
    // variables
    char* seed_url = argv[1];
    char* dirname = argv[2];
    int max_depth = atoi(argv[3]);
    //const char* ITEM = "item";
    const int HT_SIZE = 150;
    //int depth = 0;
    
    //initialize structures
    hashtable_t *ht = hashtable_new(HT_SIZE);
    bag_t *bag = bag_new();

    //Insert seed URL
    if (IsInternalURL(seed_url)){
        webpage_t *webpage = webpage_new(seed_url, 0, NULL);
        bag_insert(bag, webpage);
    }
    int page_id = 1; // counter for number of pages
    //loop through bag of URLs to visit
    webpage_t *webpage;
    while ( (webpage = bag_extract(bag)) != NULL){
        if (webpage_fetch(webpage)){
            write_to_dir(dirname, webpage, page_id);
            page_id ++;
            
            if (webpage_getDepth(webpage) < max_depth){
                pagescanner(bag, ht, webpage);
            }
        }
        else {
            fprintf(stderr, "failed to fetch webpage %s\n", webpage_getURL(webpage));
        }
        webpage_delete(webpage);
        //webpage = bag_extract(bag); 
    }
    hashtable_delete(ht, itemdelete);
    bag_delete(bag, itemdelete);
    //printf("Done\n");
}

void itemdelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}

/* Finds Webpages that are linked to in the given webpage and, if they're valid, adds them to the given bag and hashtable*/
void pagescanner(bag_t *bag, hashtable_t *ht, webpage_t *page)
{
    int pos = 0;
    char *result;
 
    while ((pos = webpage_getNextURL(page, pos, &result)) > 0) {
        if ( NormalizeURL(result)){
            if (IsInternalURL(result)){
                printf("Found url: %s\n", result);
                char* item = malloc(sizeof(char) *5);
                strcpy(item, "item");
                if (hashtable_insert(ht, result, item)){
                    webpage_t *new_page = webpage_new(result, webpage_getDepth(page) +1, NULL);
                    bag_insert(bag, new_page);
                } else {
                    free(item);
                }
                
            }
            else {
                fprintf(stderr, "Ignored non-internal URL %s\n", result);
            }
        } else {
            fprintf(stderr, "URL %s cannot be normalized\n", result);
        }
        free(result);
    }
}