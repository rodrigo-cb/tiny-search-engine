#Testing Script for indexer.c and indextest.c

# Error cases
./indexer one two three four
./indexer nonexistentDir outfile
./indexer DESIGN.md outfile

# Index into indexer.out
./indexer crawl_dir indexer.out

# Read from indexer.out, and save into indextest.out
./indextest indexer.out indextest.out