// James Cely
// ECE 2230 001 Fall 2017
// Purpose: The list module manages functions for implementing a double linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "read_book.h"

struct book
{
    int book_number;
    char file_name[MAX_STRING_SIZE];
    char book_title[MAX_STRING_SIZE];
    int number_lines;
    int total_words;
    int unique_words;
};

struct book *book_init(void)
{
    struct book *new_book;
    new_book = calloc(1,sizeof(struct book));
    return (new_book);
};

/*
    The function book_read
*/
int book_read(struct book *book, int book_number, char file_name[MAX_STRING_SIZE])
{
    FILE *file_pointer; // Declare a file pointer variable.
    char string_buffer[MAX_STRING_SIZE];    // Declare a string buffer.
    char char_buffer[MAX_STRING_SIZE];  // Declare a character buffer
    int index = 0;
    int book_title = FALSE;

    if(book != NULL)
    {
        if(book_number >= 0)
        {
            file_pointer = fopen(file_name, "r");
            if(file_pointer != NULL)
            {
                while(fscanf(file_pointer, "%c", char_buffer) > 0)
                {
                    switch (character_type(char_buffer[0]))
                    {
                    case Character:
                        string_buffer[index] = char_buffer[0];
                        string_buffer[index+1] = '\0';
                        index++;
                        break;
                    case New_line:
                        book->number_lines++;
                        strcpy(string_buffer, "");
                        break;
                    case Space:
                        if(!book_title)
                        {
                            strcpy(book->book_title, string_buffer);
                            book_title = TRUE;
                        }
                        book->total_words++;
                        strcpy(string_buffer, "");
                        index = 0;
                        break;
                    }
                }
            }
            fclose(file_pointer);
        }
    }
    return (-1);    // Return -1 to indicate an error.


    return (0);
}

int book_print(struct book *book)
{
    printf("%s\n",book->book_title);
    printf("Number of lines processed\t%6d\n",book->number_lines);
    printf("Number of words processed\t%6d\n",book->total_words);
    printf("Number of unique words\t\t%6d\n",book->unique_words);

    return (1);
};

int character_type(char character)
{
    if((character == ' ') || (character == 26)) return (Space);
    if(character == '\n') return (New_line);
    if(character == '\0') return (Null_char);
    return (Character);
}
