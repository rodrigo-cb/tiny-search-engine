## README
---
# CS50 querier

Rodrigo A. Cavero Blades - Winter 2019

This querier was built to satisfy the following [requirements](https://github.com/cs50spring2021/tse-labs/blob/main/querier/REQUIREMENTS.md)

To build, run `make`. (if libcs50.a and common.a aren't already made, make them first, or run make from top-level directory to make everything)

To clean up, run `make clean`.

The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

# Usage:

./querier pageDirectory indexFilename

where *pageDirectory* is the name of the TSE crawler-produced directory

where *indexFilename* is the name of the TSE indexer-produced file

# Return Values:
* 0: No errors.
* 1: Wrong number of input arguments.
* 2: pageDirectory is not an existing directory produced by the crawler
* 3: filename is not a readable file

# Assumptions:

pageDirectory has files named 1, 2, 3, …, without gaps.

The content of files in pageDirectory follow the following format: 
1st line contains URL, 2nd line contains page depth, rest of file contains html

the directory name given will not contain a '/'.

A single query will not contain more than 100 words.

The *indexFilename* file contains one line per word, one word per line,
each line provides the word and one or more (docID, count) pairs, in the format
word docID count [docID count]…
