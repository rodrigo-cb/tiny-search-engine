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

bool isCrawlerDirectory(char *dir);

void read_from_dir(char* dirname, bag_t *bag);

#endif
