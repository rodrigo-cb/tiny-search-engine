## README
---
# CS50 Crawler

Rodrigo A. Cavero Blades - Winter 2019

This Crawler was built to satisfy the following [requirements](https://github.com/cs50spring2021/tse-labs/blob/main/querier/REQUIREMENTS.md) 

To build, run `make`. (if libcs50.a and common.a aren't already made, make them first, or run make from top-level directory to make everything)

To clean up, run `make clean`.

The TSE crawler is a standalone program that crawls the web and retrieves webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.

The crawler pauses for one second in between page fetches.

# Usage:

./crawler seedURL pageDirectory maxDepth

where *seedURL* is used as the initial URL (must be an internal URL).

where *pageDirectory* is the pathname for an existing directory in which to write downloaded webpages.

where *maxDepth* is a non-negative integer representing the maximum crawl depth.

# Return Values:
* 0: No errors.
* 1: Wrong number of input arguments.
* 2: Seed URL can't be normalized.
* 3: Non-internal seed URL.
* 4: Directory doesn't exist or is not writeable.
* 5: MaxDepth is not a valid number.

# Assumptions:
No relevant assumptions other than those made clear above.



