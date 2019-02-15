# CS50 Lab 5
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### TESTING
---
Testing was performed using the testing script `test_indexer.sh`.

This tests some error cases:
* nonexistent directory
* wrong number of arguments
* dirName given is not a directory

Then, it performs a succesful indexing of the pages contained in the crawler-produced directory `crawl_dir`

The output from this testing script can be found in `test_script.out`, produced with:

./test_indexer.sh &> test_script.out

The test also produced the files `indexer.out`, which is the result of running indexer, and `indextest.out`, which is the file produced by indextest after loading the index from `indexer.out`

I made sure that `indexer.out` contained the correct count of words and pageIDs they were found on (by personally looking at each file in crawl_dir).

I also personally compared `indexer.out` and `indextest.out` and made sure that they both contained the same words and (pageID:count) pairs for each word.

I ran valgrind on both indexer and indextest and made sure no memory leaks or errors were possible.