# CS50 Lab 5
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### TESTING
---
Testing was performed using the testing script `querier_test.sh`, as well as manually typing the queries that are shown (commented out) on the testing script.

This tests some error cases:
* wrong number of arguments
* invalid dirname
* invalid filename

Then, it performs some succesful query searches. 

The output from this testing script can be found in `querier_test_out`, produced with:

./querier_test.sh &> querier_test_out

(as well as manually typing some queries)

The files needed for this are `crawl_dir` and `index_file`.

I went through the test results and through the relevand entries in the index file to make sure it was performing the right operations.

I ran valgrind on both indexer and indextest and made sure no memory leaks or errors were possible.