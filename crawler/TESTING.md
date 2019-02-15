# CS50 Lab 4
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### TESTING
---
Testing was performed using the testing script `crawl_test.sh`.

This tests a variety of error cases:
* nonexistent domain
* wrong number of arguments
* nonexistent webpage in internal domain
* non-internal seed URL
* Negative number given on maxDepth
* Non-number given on maxDepth
* pageDirectory that doesnt exist

As well as one success case (or more, depending on which lines of crawl_test.sh are commented/uncommented).

The results from testing can be found in crawl_test.out, produced with:

./crawl_test.sh &> crawl_test.out

Aside from this testing file, I used valgrind to ensure no memory leaks or errors were possible.