// James Cely
// ECE 2230 001 Fall 2017
// Purpose: The list module manages functions for implementing a double linked list.

#ifndef READ_BOOK_H_INCLUDED
#define READ_BOOK_H_INCLUDED

typedef struct book *book;

struct book *book_init(void);

int book_read(struct book *book, int book_number, char file_name[MAX_STRING_SIZE]);

int book_print(struct book *book);

int character_type(char character);

#endif // READ_BOOK_H_INCLUDED
