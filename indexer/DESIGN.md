## DESIGN
---
# CS50 indexer

Rodrigo A. Cavero Blades - Winter 2019

The index we are creating will map from word to (pageID : count) pairs, representing the number of occurencess of that word in the document with id pageID. 

We will design a data structure to represent this inverted index, its name will be index.

Indextest will read a indexer-produced file and recreate an index data structure from this information, after that it will save (print) this recreated index into a second file, so we can see if both files contain the same information.

Words that are less than 3 characters long are ignored, and all words are converted to lower-case.

#### Very high-level description of the indexer and indextest:

indexer:

* Process and validate command-line parameters
* Initialize data structure index
* index_build(directory, index)
* index_save(file, index);
* clean up data structures

indextest:

* Process and validate command-line parameters
* Initialize data structure index
* index_load(file1, index)
* index_save(file2, index)
* clean up data structures

The resulting file contains one line per word, one word per line
each line provides the word and one or more (docID, count) pairs, in the format
word docID count [docID count]…