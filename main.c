// James Cely
// ECE 2230 001 Fall 2017
// Purpose: The list module manages functions for implementing a double linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "read_book.h"
#include "list.h"
#include "hash.h"

int main(int argc, char *argv[])
{
    int index;  // Declare an index variable.
    int total_books = 0;    // Declare an integer to hold the total number of books to be analyzed.
    int command_line = TRUE;   // Declare an integer to determine if the file names were entered on the command line or not.
    FILE *file_pointer; // Declare a file pointer.
    char string_buffer[MAX_STRING_SIZE];    // Declare a string for storing temporary values.

    total_books = argc - 1; // Compute the total number of book files entered as command line arguments.

    while((total_books < 2) || (total_books > MAX_BOOKS))   // Ask the user for the number of books to be analyzed until a valid number is entered.
    {
        command_line = FALSE;   // Set the value of command line to false.
        printf("Please Enter The Number Of Book Files To Be Analyzed (Must Be Between 2-10): ");   // Ask the user for the number of book files to be analyzed.
        scanf("%d", &total_books);  // Store the total number of books from keyboard input.
    }

    struct book *book[total_books];    // Declare an array of books.

    for(index = 0; index < total_books; index++)    // Loop once for each book to be initialized.
    {
        book[index] = book_init();  // Allocate memory for each book.
    }

    for(index = 0; index < total_books; index++)    // Loop once for each book.
    {
        if(command_line)    // If command line is true then get the file name from the command line.
        {
            file_pointer = fopen(argv[index+1],"r");    // Attempt to open the file.
            while(file_pointer == NULL)  // Check to see if the file successfully opened.
            {
                printf("**ERROR: Invalid File Name: %s **\n", argv[index+1]); // Print error message.
                printf("Please Enter The File Name Of Book %d: ",index+1);  // Ask the user to input the file name.
                scanf("%s", string_buffer);   // Store the file name.
                file_pointer = fopen(string_buffer, "r"); // Attempt to open the file.
            }
            book_read(book[index], index, argv[index+1]);
            fclose(file_pointer);   // Close the file.
        }
        if(!command_line)   // If command line is not true then get the file name from the user.
        {
            printf("Please Enter The File Name Of Book %d: ",index+1);  // Ask the user to input the file name.
            scanf("%s", string_buffer);   // Store the file name to the array.
            file_pointer = fopen(string_buffer, "r"); // Open the file.
            while(file_pointer == NULL)  // Check to see if the file successfully opened.
            {
                printf("**ERROR: Invalid File Name. **\n"); // Print error message.
                printf("Please Enter The File Name Of Book %d: ",index+1);  // Ask the user to input the file name.
                scanf("%s", string_buffer);   // Store the file name.
                file_pointer = fopen(string_buffer, "r"); // Open the file.
            }
            book_read(book[index], index, string_buffer);
            fclose(file_pointer);    // Close the current file.
        }
    }

    /* Begin printing book information. */
    printf("ECE 2230 Fall 2017 Text Hashing Project\n");    // Print menu title.
    printf("James Cely\n"); // Print name.

    for(index = 0; index < total_books; index++)
    {
        book_print(book[index]);
    }



    return 0;
}


