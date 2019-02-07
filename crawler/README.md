## README
```
# CS50 Crawler

Rodrigo A. Cavero Blades - Winter 2019

To build, run `make`.

To clean up, run `make clean`.

The TSE crawler is a standalone program that crawls the web and retrieves webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.

The crawler pauses for one second in between page fetches.

# Usage:

./crawler seedURL pageDirectory maxDepth

where *seedURL* is used as the initial URL (must be an internal URL),
where *pageDirectory* is the pathname for an existing directory in which to write downloaded webpages, and
where *maxDepth* is a non-negative integer representing the maximum crawl depth

# Assumptions:
No relevant assumptions other than those made clear above.

```

