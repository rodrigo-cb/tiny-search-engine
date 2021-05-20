## README
---
# CS50 indexer

Rodrigo A. Cavero Blades - Winter 2019

This Indexer was built to satisfy the following [requirements](https://github.com/cs50spring2021/tse-labs/blob/main/indexer/REQUIREMENTS.md) 

To build, run `make`. (if libcs50.a and common.a aren't already made, make them first, or run make from top-level directory to make everything)

To clean up, run `make clean`.

The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

# Usage:

./indexer pageDirectory filename

where *pageDirectory* is the name of the crawler-produced directory

where *filename* is the name of the output file

# Return Values:
* 0: No errors.
* 1: Wrong number of input arguments.
* 2: pageDirectory is not an existing directory produced by the crawler
* 3: filename is not a writeable file

# Assumptions:

pageDirectory has files named 1, 2, 3, …, without gaps.

The content of files in pageDirectory follow the following format: 
1st line contains URL, 2nd line contains page depth, rest of file contains html

the directory name given will not contain a '/'.
