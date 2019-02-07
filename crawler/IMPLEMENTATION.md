# CS50 Lab 4
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### IMPLEMENTATION
---
The crawler makes use of the *libcs50.a* library, specifically the *bag* module and the *hashtable* module.

The *bag* is used to store the websites which need to be visited, initially just the seedURL.
The *hashtable* is used to store the URLs which have already been seen, so no duplicate webpages are visited and stored in the directory.

The hashtable implemented here was set to have a size of 150, which should be enough for the usage we expect from this program.

Because the *bag* makes no promises as to the order of elements retrieved from it, the crawl may or may not end up being a DFS.

Additionally, the crawler also makes use of the *webpage* module in the *libcs50* library to fetch the html from websites and scan them for more URLS to visit.

Finally it makes use of the *pagedir* module in the *common/* directory. This is used to write the websites found into files in the pageDirectory given.

The functionality of *crawler.c* can be mainly divided into:
* *main*: High-level logic, basically calls check_input and crawl
* *check_input*: Makes sure the input is valid, cheching for correct number of arguments, types of arguments, and validity of seed URL.
* *crawl*: performs the actual web-crawl loop, calls *pagescanner*
* *pagescanner*: Finds URLs that are contained in the current webpage, and (if internal and new) adds them to the *bag* and *hashtable* so the crawl loop visits them.