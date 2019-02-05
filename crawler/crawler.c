#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "pagedir.h"


bool check_input(int argc, char *argv[]);
void crawl(char *argv[]);
void itemdelete(void* item);


int main(int argc, char *argv[]) 
{
    if (check_input(argc, argv)){
        crawl(argv);
        return 0;
    }
    return 1;
}

bool check_input(int argc, char *argv[])
{
    //Check for correct number of parameters
    if (argc != 4){
        fprintf(stderr, "Usage: ./crawler seedURL pageDirectory maxDepth\n");
        return false;
    }

    // Check if directory exists and is writable by trying to create a file there

    char *string = malloc(strlen(argv[2]) + 10);
    if (string == NULL) {
        fprintf(stderr, "Error allocating memory with malloc\n");
        return false;
    }
    string[0] = '\0';
    strcat(string, argv[2]);
    strcat(string, "/.crawler");
    FILE *f = fopen(string, "w");
    printf("%s\n", string);
    free(string);
    if (f == NULL){
        fprintf(stderr, "The directory doesn't exist or is not writable\n");
        return false;
    }
    fclose(f);

    //Check if maxdepth is valid
    int num = atoi(argv[3]);
    if (num == 0 && argv[3][0] != '0'){
        fprintf(stderr, "maxDepth is not a valid number\n");
        return false;
    }
    return true;
}
void crawl(char *argv[])
{
    // variables
    char* seed_url = argv[1];
    char* dirname = argv[2];
    int max_depth = argv[3];
    const char* ITEM = "item";
    const int HT_SIZE = 150;
    int depth = 0;
    
    //initialize structures
    hashtable_t *ht = hashtable_new(HT_SIZE);
    bag_t *bag = bag_new();

    //Insert seed URL
    bag_insert(bag, seed_url);
    
    //loop through bag of URLs to visit
    for (char*url = bag_extract(bag); url != NULL; ){
        if (IsInternalURL(url)){
            webpage_t *webpage = webpage_new(url, depth, NULL);
            webpage_fetch(webpage);
            write_to_dir(dirname, webpage);
            if (depth < max_depth){
                bag_insert(bag, url);
                hashtable_insert(ht, url, ITEM);
            }
            free(webpage);
            url = bag_extract(bag);
            depth ++;
        }
        
    }
    hashtable_delete(ht, itemdelete);
    bag_delete(bag, itemdelete);
    free(ht);
    free(bag);
}

void itemdelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}