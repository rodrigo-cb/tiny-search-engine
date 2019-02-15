/* 
 * indextest.c - Test program for indexer.c
 * Reads an index from a file and writes it into a new file to test indexer functionality
 */

#include <stdio.h>
#include "index.h"
int main(int argc, char *argv[]) 
{
    if (argc != 3){
        fprintf(stderr, "Usage: ./indextest oldIndexFilename newIndexFilename\n");
        return 1;
    }
    index_t *idx = index_load(argv[1]);
    index_save(idx, argv[2]);
}