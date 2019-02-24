# CS50 Lab 5
## Rodrigo A. Cavero Blades, CS50 Winter 2019

### IMPLEMENTATION
---
The querier makes use of the *libcs50.a* and *common.a* libraries.

The functionality of *querier.c* can be mainly divided into:

* *main*: High-level logic, calls check_input, loads index, calls process_query, then cleans up.

* *process_query*: Validates query, then parses query into an array of words, which is passed to run_query along with 
the index and URL of the crawler-produced directory of pages.

* *run_query*: First, this method makes use of two functions, *counters_sum* and *counters_product*, 
to intersect and merge the *counters_t* counters representing each of the query's words
until a final resulting *counters* remains, containing the information of the matches to the entire query. Then, it ranks the matches in order of their scores, utilizing the *counters_iterate* function of the counters module, to insert the documents in order into an array of structs
representing each document, score, and ID. This array of structs is then printed in order and according to the format defined in the Design spec. 
