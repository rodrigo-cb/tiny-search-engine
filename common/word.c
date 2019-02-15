/* 
 * word.c - CS50 'word' module
 * 
 */

#include <string.h>
#include <ctype.h>
#include "word.h"

/**************** make_lower_case() ****************/
void make_lower_case (char ** word_address)
{
    char *word = *word_address;
    for(int i = 0; i < strlen(word) ; i++){
        word[i] = tolower(word[i]);
    }
}