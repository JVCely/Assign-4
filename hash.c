// James Cely
// ECE 2230 001 Fall 2017
// Purpose: The list module manages functions for implementing a double linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "hash.h"

struct book_word
{
    char word[MAX_STRING_SIZE];
    int book_count[MAX_BOOKS];

};
