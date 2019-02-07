
./crawler one two three four five
./crawler http://non-existent-website19837.edu/page/ data 2
./crawler https://en.wikipedia.org/wiki/Science/ data 1
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/nonexistentwebpage/ data 2
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ data -35
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ data WORD
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/s NonExistentDir 1

## Uncomment one of these to run a crawler test on one of the CS50 playground websites
## Change the last parameter to change the max depth

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ data 3
#./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ data 1
#./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ data 1