/* 
 * pagedir.h - header file for CS50 'pagedir' module
 * 
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

/**************** global types ****************/
//typedef struct pagedir pagedir_t;  // opaque to users of the module, users do not know and cannot access members of this struct

/**************** functions ****************/

/* Write the given webpapge into a file in the given directory. */
void write_to_dir (char* dirname, webpage_t *page, int id);

#endif
