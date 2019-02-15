# CS50 Lab 4
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### IMPLEMENTATION
---
The indexer makes use of the *libcs50.a* and *common.a* libraries.

The *index.c* module defines the *index_t* data structure, which was created to represent the inverted index of words to (pageID:count) pairs and was implemented as a special case of hashtable which contains string pointers as keys (for words) and *counters_t* pointers as values (for pageID:count pairs).

The index implemented here was set to have a size of 600, which is a reasonable size for the usage we expect from this program.

The functionality of *indexer.c* can be mainly divided into:
* *main*: High-level logic, calls check_input, build_index, index_save, then cleans up.
* *check_input*: Makes sure the input is valid, cheching for correct number of arguments, and validating them.
* *build_index*: with the help of *pagedir.c*, fills a *bag* structure with *webpage_t* structs containing the URL and HTML of each website represented in each file in the crawler-produced directory given, as well as the PageID of the file it was found on. Because we don't need to know their depth, the depth field of *webpage_t* struct is instead used to save the PageID of the file which represented the webpage.
* *index_save*: A function of the *index* data structure we implemented, this saves the *index* into a file with the filename given, the format is that which was described in DESIGN.md.