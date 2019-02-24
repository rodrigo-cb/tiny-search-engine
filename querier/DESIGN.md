## DESIGN
---
# CS50 querier

Rodrigo A. Cavero Blades - Winter 2019

The querier will read queries from the user, and print a list of matching documents in ranked order.

Queries are a sequence of words, with optional boolean operators (‘and’, ‘or’), where ‘and’ has higher precedence than ‘or’.

#### High-level description of the querier and main functions:

querier:

* validate command-line parameters
* Load index from memory.
* Process the query from stdin, using indexer, until EOF. (process_query)
* index_save(index, filename);
* clean up data structures

process_query:

* Validate query
* Extract and normalize words from the query
* Run the query (run_qury)
* clean up data structures

run_query:

* Compute a sum of the products of the *counters_t* counters representing each word's matches
* Utilize functions to merge and intersect *counters* for the "and" and "or" operators respectively
* Rank the matches in the resulting *counters*  
* Print the ordered list of matching documents

Each item in the resulting ranked list will be printed in the following format:

* Score: __ DocID: __ URL