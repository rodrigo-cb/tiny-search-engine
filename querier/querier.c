#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "index.h"
#include "file.h"
#include "memory.h"
#include "word.h"
#include "pagedir.h"
#include "counters.h"


/* 
 * querier.c - CS50 'querier' program
 * The TSE Querier is a standalone program that reads the index file produced 
 * by the TSE Indexer, and page files produced by the TSE Querier, and answers 
 * search queries submitted via stdin.
 * 
 */

/**************** local types ****************/
typedef struct two_ctrs {
  counters_t *c1;
  counters_t *c2;
} two_ctrs_t;

typedef struct document {
  int score;
  int ID;
  char * URL;
} document_t;

typedef struct arr_and_string {
  document_t ** arr;
  int length;
  char * string;
} arr_and_string_t;

/**************** Function Prototypes ****************/
int check_input(int argc, char *argv[]);
void process_query(index_t *idx, char * dirname);
int exctract_words(char * line, const char* arr[]);
bool check_query(const char * arr[], int count);
void run_query(index_t *idx, char * dirname, const char * arr[], int size);
bool is_operator (const char *word);

counters_t* ctrs_product (index_t *idx, const char * arr[], int curPos, 
int * posAddress, int arr_size);

counters_t* ctrs_sum (index_t *idx, const char * arr[], int size);

static void counters_merge(counters_t *ctrs_A, counters_t *ctrs_B);
static void counters_merge_helper(void *arg, const int key, int count_B);
static void counters_intersect(counters_t *ctrs_A, counters_t *ctrs_B);
static void counters_intersect_helper(void *arg, const int key, int count_A);

static void matches_count(void *arg, const int key, int count);
static void matches_sort(void *arg, const int docID, int myScore);

/******************************************************/
int main(int argc, char *argv[]) 
{
    char *dirname = argv[1];
    char *idx_filename = argv[2];
    
    int error_code;
    if ( (error_code = check_input(argc, argv)) != 0){
        return error_code;
    }
    // Load index from file
    index_t *index = assertp(index_load(idx_filename), "Error loading index from file");

    // Process Query from stdin
    process_query(index, dirname);
    // Cleanup
    index_delete(index);
    return 0;
}

/* 
* Makes sure input is valid
*/
int check_input(int argc, char *argv[])
{
    //Check for correct number of parameters
    if (argc != 3){
        fprintf(stderr, "Usage: ./querier pageDirectory indexFilename\n");
        return 1;
    }
    //Validate directory name
    if ( ! isCrawlerDirectory(argv[1])){
        fprintf(stderr, "pageDirectory is not an existing directory produced by the crawler\n");
        return 2;
    }
    //Validate file name
    FILE *fp; 
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        fprintf(stderr, "indexFilename is not a readable file\n");
        return 3;
    }
    fclose(fp);
    return 0;
}

/* 
* Processes each query
*/
void process_query(index_t *idx, char * dirname)
{
//     1. while (line = getting a new line from stdin) // readlinep()
// 1.0 extract the words, normalize it (extract_words(line, words))
// 1.1 if we have non-zero words
// 1.2 	if (check the validity of query) (check_query(words))
// 1.3 	run_query(words)
// 1.4 	clean up memory (line or more)

    // Max number of words we expect on a single query
    const int MAX_QUERY_SIZE = 100;

    const char * words[MAX_QUERY_SIZE];
    
    printf("Please enter your query\n");

    // Read Queries from stdin
    char *line;
    while ( (line = readlinep(stdin) ) != NULL){
        // Extract each word from the query
        // and keep track of how many we extracted
        int word_count = exctract_words(line, words);

        // If it's a valid query...
        if (word_count > 0 && check_query(words, word_count)){
            // Print cleaned-up query
            printf("Query:");
            for (int i = 0; i < word_count; i ++){
                printf(" %s", words[i]);
            }
            printf("\n");

            //Run the query
            run_query(idx, dirname, words, word_count);
        }
        // Cleanup
        free(line);
    }
}

/* 
* Extracts all words from the given string, makes them lowercase, and inserts them into the given array
*/
int exctract_words(char * line, const char* arr[])
{
    char *rest = line;
    int count = 0; // index of current word
    while (true){
        char *word = rest;
        while (isspace(*word)){
            word++;
        }
        rest = word;
        while (isalpha(*rest)){
            rest++;
        }
        if (isspace(*rest)){
            //found end of word
            *rest = '\0';
            rest ++;
            make_lower_case(&word);
            arr[count] = word;
            count ++;
        }
        else{
            if (*rest == '\0') {
                make_lower_case(&word);
                arr[count] = word;
                return ++count;
            }
            fprintf(stderr, "invalid character \'%c\' in query\n", *rest);
            return -1;
        }
    }
    
}

/* 
* Checks for invalid query. Returns true if query is valid, otherwise returns false
*/
bool check_query(const char * arr[], int count)
{
    // check for empty query
    if (arr[0] == NULL || strcmp(arr[0], " ") == 0 || strcmp(arr[0], "") == 0){
        return false;
    }

    //check for operator at beginning or end
    if ( is_operator(arr[0]) || is_operator(arr[count-1]) ){
        printf("Error: the words: \"and\" \"or\" cannot be first or last\n");
        return false;
    }

    //check for consecutive operators
    for (int i = 0; i < count -2; i ++){
        if (is_operator(arr[i]) && is_operator(arr[i+1])){
            printf("Error: cannot have two consecutive operators\n");
            return false;
        }
    }
    // Valid query
    return true;

}

/* 
* Searches for matches to the query in our index of document pages,
* scores them and prints a resulting list of documents in ranked order.
*/
void run_query(index_t *idx, char * dirname, const char * arr[], int size)
{
    counters_t *result = ctrs_sum(idx, arr, size);
    // printf("Done!!!\n");
    // counters_print(result, stdout);

    // Count the number of matches
    int num_matches = 0;
    counters_iterate(result, &num_matches, matches_count);
    if (num_matches == 0){
        printf("No matches\n");
        return;
    }

    // Rank the matches by score

    // Create a clean array to use as the ranked list
    document_t *ranked_list[num_matches];
    memset(ranked_list, '\0', sizeof(ranked_list));

    // Package information for needed for ranking into struct
    arr_and_string_t *arr_and_s = malloc (sizeof(arr_and_string_t));
    arr_and_s->arr = ranked_list;
    arr_and_s->length = num_matches;
    arr_and_s->string = dirname;

    // Rank the matches by score
    // Iterate over the counters, passing the packaged information
    counters_iterate(result, arr_and_s, matches_sort);

    // Print the ranked matching documents
    printf("Matches %d documents (ranked) :\n", num_matches);
    for (int i = 0; i < num_matches; i ++){
        document_t *doc = ranked_list[i];
        printf("Score: %d, docID: %d : %s\n", doc->score, doc->ID, doc->URL);
    }

    //Cleanup
    for (int i = 0; i < num_matches; i ++){
        document_t *doc = ranked_list[i];
        free(doc->URL);
        free(doc);
    }
    counters_delete(result);
    free(arr_and_s);
}

/* 
* Returns true if word is "and" or "or"
*/
bool is_operator (const char *word){
    if( (strcmp (word, "and") == 0) || (strcmp(word, "or") == 0) ){
        return true;
    }
    return false;
}

/* 
* Computes a product of counters items
*/
counters_t* ctrs_product (index_t *idx, const char * arr[], int pos, int * posAddress, int arr_size) {
    const char * word = arr[pos];
    counters_t *running_product = index_find(idx, word);
    for (int i = pos + 1; i < arr_size; i ++){
        word = arr[i];
        *posAddress = i;
        if (strcmp(word, "and") == 0){
            continue;
        }
        if (strcmp(word, "or") == 0){
            *posAddress += 1;
            return running_product;
        }
        counters_intersect(running_product, index_find(idx, word));
    }
    *posAddress += 1;
    return running_product;
}

/* 
* Computes a running sum of counters items
*/
counters_t* ctrs_sum (index_t *idx, const char * arr[], int size) {
    counters_t *running_sum = counters_new();
    // for (int i = 0; i < size; i++){
    //     char * word = arr[i];
    // }
    int pos = 0;
    while (pos < size){
        //printf("Pos is: %d\n", pos);
        counters_t *product = ctrs_product(idx, arr, pos, &pos, size);
        // printf("printing prod:\n");
        // counters_print(product, stdout);
        counters_merge(running_sum, product);
        //printf("printing partial running sum:\n");
        //counters_print(running_sum, stdout);
    }
    // printf("printing final running sum:\n");
    // counters_print(running_sum, stdout);
    return running_sum;
}

/* 
* Merges two counters
*/
static void 
counters_merge(counters_t *ctrs_A, counters_t *ctrs_B)
{
  counters_iterate(ctrs_B, ctrs_A, counters_merge_helper);
}

/* 
* Helper for counters_merge
*/
static void 
counters_merge_helper(void *arg, const int key, int count_B)
{
  counters_t *ctrs_A = arg;
  //int *itemB = item;
  
  // find the same key in setA
  int count_A = counters_get(ctrs_A, key);
  if (count_A == 0) {
    // not found: insert it
    counters_set(ctrs_A, key, count_B);
    //printf("\t%s added\n", key);
  } else {
    // add to the existing value
    counters_set(ctrs_A, key, counters_get(ctrs_A, key) + count_B);
    //printf("\t%s exists\n", key);
  }
}

/* 
* Intersects two counters
*/
static void 
counters_intersect(counters_t *ctrs_A, counters_t *ctrs_B)
{
    //printf("IN COUNTERS INTERSECT \n");
    two_ctrs_t *two_ctrs = malloc(sizeof(two_ctrs_t));
    two_ctrs->c1 = ctrs_A;
    //printf("COUNTERS A: \n");
    // counters_print(ctrs_A, stdout);
    two_ctrs->c2 = ctrs_B;
    //printf("COUNTERS B: \n");
    counters_iterate(ctrs_A, two_ctrs, counters_intersect_helper);

    //printf("RESULT: \n");
    //counters_print(two_ctrs->c1, stdout);
    free(two_ctrs);
  
}

/* 
* Helper for counters_intersect
*/
static void 
counters_intersect_helper(void *arg, const int key, int count_A)
{
    two_ctrs_t *two_ctrs = arg;

    int count_B = counters_get(two_ctrs->c2, key); 
    if (count_B == 0) {
        // not found this key in counters B, set the int to zero
        counters_set(two_ctrs->c1, key, 0);
        //printf("Setting key %d to 0\n", key);
    } else {
        // found the key, take the minimum
        count_A = count_A < count_B ? count_A : count_B;
        counters_set(two_ctrs->c1, key, count_A);
        //printf("Setting key %d to %d\n", key, count_A);
    }
}


/* 
 * counts the number of non-zero count key-count pairs in counter
 */
static void matches_count(void *arg, const int key, int count)
{
  int *n_matches = arg;

  if (n_matches!= NULL && count != 0)
    (*n_matches)++;
}

/* 
 * Inserts document matches into an array, sorted by score
 */
static void matches_sort(void *arg, const int docID, int myScore)
{
    // Ignore docs with no matches (score 0)
    if (myScore == 0){
        return;
    }

    // Unpackage the what we need to work with
    arr_and_string_t *arr_and_s = arg;

    document_t **arr = arr_and_s->arr;
    int arr_length = arr_and_s ->length;
    char * dirname = arr_and_s->string;

    //Get the document's URL using a function from pagedir.c
    char *URL = get_doc_URL(dirname, docID);

    // Initialize Struct
    document_t *this_doc = malloc (sizeof(document_t));
    this_doc -> score = myScore;
    this_doc -> ID = docID;
    this_doc -> URL = URL;
    

    // Insert doc into correct place in the array. 
    // (Insertion Sort style)
    int i = 0;
    while (i < arr_length){
        document_t *doc = arr[i];
        if (doc == NULL) {
            arr[i] = this_doc;
            return;
        } 
        if (doc->score < myScore) {
            for (int j = arr_length - 2; j >= i; j --){
                arr[j + 1] = arr[j];
            }
            arr[i] = this_doc;
            return;
        } 
        i ++;
    }
}