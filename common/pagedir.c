/* 
 * pagedir.c - CS50 'pagedir' module
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "pagedir.h"
#include "memory.h"

char* CRAWL_MARK = ".crawler";  // Name of file left by crawler when creating a directory of crawled webpages

/* Write the given webpapge into a file in the given directory. */
void write_to_dir (char* dirname, webpage_t *page, int id)
{

    //first convert the id to string
    int id_length = snprintf( NULL, 0, "%d", id);  //to get the lenght of the id string
    char *id_str = malloc(id_length + 1);
    snprintf(id_str, id_length + 1, "%d", id);

    char *file_name = malloc(strlen(dirname) + strlen(id_str) + 2);
    file_name[0] = '\0';        // make sure we have a clean string
    strcat(file_name, dirname);
    strcat(file_name, "/");
    strcat(file_name, id_str);
    FILE *fp = fopen(file_name, "w");
    free(id_str);
    if (fp != NULL){
        fprintf(fp, "%s\n", webpage_getURL(page));
        fprintf(fp, "%d\n", webpage_getDepth(page));
        fprintf(fp, "%s\n", webpage_getHTML(page));
        fclose(fp);
    } else {
        fprintf(stderr, "Error making the file %s\n", file_name);
    }
    free(file_name);
}

/* Returns true if a given directory was made by our crawler. Returns false if it's not crawler-produced,
dir doesn't exist, dir is not a valid pathname, not a directory, or not a readable directory */

bool isCrawlerDirectory(char *dir)
{
    //validate pointers
    assertp(dir, "isCrawlerDirectory received null dir");

    int buffer_size = strlen(dir) + strlen(CRAWL_MARK) + 2; 
    char file_name[buffer_size];
    sprintf(file_name, "%s/%s", dir, CRAWL_MARK);
    
    FILE *fp = fopen(file_name, "w");

    if (fp == NULL){
        return false;
    } 
    fclose(fp);
    return true;
}

/* Reads from crawler-produced directory. Saves webpages (saving their IDs into the webpage's 'depth' field) into the given bag. */
void read_from_dir(char* dirname, bag_t *bag)
{   
    //validate pointers
    assertp(dirname, "read_from_dir received null dirname");
    assertp(bag, "read_from_dir received null bag");

    FILE *fp;
    int dir_length = strlen(dirname);

    // Lenght of dirname + lenght of '/' + max lenght of integer + lenght of null character
    int buffer_size = dir_length + 10 + 1 + 1; 

    char filename[buffer_size];
    sprintf(filename, "%s/1", dirname);

    int id_num = 1;  // ID of first file is 1

    // While there are files to open in the directory
    while( (fp = fopen(filename, "r")) != NULL ){ 

        char *url = readlinep(fp);       // get page url
        free(readlinep(fp));             // ignore page depth
        char *html = readfilep(fp);      // get page html

        fclose(fp);

        // Create webpage and insert into given bag
        // Insert ID_num into webpage_t depth field (we don't need to keep track of depth)
        webpage_t *webpage = assertp(webpage_new(url, id_num, html), "Error Initializing webpage");
        free(url);
        bag_insert(bag, webpage);

        // Filename will take the name of the next file in the directory
        id_num ++; 
        filename[dir_length + 1] = '\0';
        char file_id[10];
        sprintf(file_id, "%d", id_num);
        strcat(filename, file_id);
    }
}