/* 
 * indextest.c - Test program for indexer.c
 * Reads an index from a file and writes it into a new file to test indexer functionality
 */

#include <stdio.h>
#include "index.h"
#include "memory.h"

int main(int argc, char *argv[]) 
{
    if (argc != 3){
        fprintf(stderr, "Usage: ./indextest oldIndexFilename newIndexFilename\n");
        return 1;
    }
    // load index from source file
    index_t *idx = assertp(index_load(argv[1]), "index_load returned null");

    // save index into target file
    index_save(idx, argv[2]);

    //cleanup
    index_delete(idx);
}