/* 
 * pagedir.h - header file for CS50 'pagedir' module
 * 
 */
#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"
#include "bag.h"

/* Write the given webpapge into a file in the given directory. */
void write_to_dir (char* dirname, webpage_t *page, int id);

/* Returns true if a given directory was made by our crawler. 
Returns false if it's not crawler-produced, dir doesn't exist, 
dir is not a valid pathname, not a directory, or not a readable directory 
*/
bool isCrawlerDirectory(char *dir);

/* Reads from crawler-produced directory. Saves webpages (saving their IDs into the 
*  webpage's 'depth' field) into the given bag. 
*/
void read_from_dir(char* dirname, bag_t *bag);

/* Returnss the URL of a document. Requires the name of a crawler-produced directory
 * and the document's ID. Caller must later free pointer of URL.
*/
char *get_doc_URL(char * dirname, int docID);

#endif
