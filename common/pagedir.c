/* 
 * pagedir.c - CS50 'pagedir' module
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"


/* Write the given webpapge into a file in the given directory. */
void write_to_dir (char* dirname, webpage_t *page, int id){
    //first convert the id to string
    int id_length = snprintf( NULL, 0, "%d", id);  //to get the lenght of the id string
    char *id_str = malloc(id_length + 1);
    snprintf(id_str, id_length + 1, "%d", id);

    char *file_name = malloc(strlen(dirname) + strlen(id_str) + 2);
    file_name[0] = '\0';
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