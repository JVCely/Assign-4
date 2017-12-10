// James Cely
// ECE 2230 001 Fall 2017
// Purpose: The list module manages functions for implementing a double linked list.

#include <stdio.h>  // Include the standard library for input / output.
#include <stdlib.h> // Include the standard library.
#include "list.h"   // Include the list.h header file.

struct list_node    // Definition of the structure list_node.
{
    struct list_node *next; // Define a pointer to the next structure of the type list_node.
    struct list_node *prev; // Define a pointer to the previous structure of the type list_node.
    list_data item_data;    // Define a pointer to the item data contained in the node.
};

struct list // Definition of the structure list.
{
    struct list_node *head; // Define a pointer to the head of the list.
    struct list_node *tail; // Define a pointer to the tail of the list.
    struct list_node *current;  // Define a pointer to the current node of the list.
};

/*
    Allocates and initializes a new empty list.
    Returns a new empty list or NULL if there was an error.
*/
list list_init(void)    // List_init allocates memory for a list and returns a pointer to that list.
{
    struct list *new_list;   // Declare a pointer for a new list.

    new_list = calloc(1,sizeof(struct list));   // Allocate memory for a structure of the type list.

    if(new_list != NULL)    // Check to ensure that the new list and new node are not NULL.
    {
        return (new_list);  // Return the new list.
    }

    return (NULL);    // Return NULL.
}

/*
    Destroys the list and frees its memory.
    Frees all memory allocated for the list. List data is not freed.
*/
void list_finalize(list list)    // List_finalize frees the memory allocated for the list.
{
    struct list_node *next_node;    // Make a pointer to hold the next node after the current node has been freed.
    struct list_node *current_node;    // Make a pointer to hold the current node.
    struct list_node *last_node;    // Declare a pointer to hold the last node.

    if(list != NULL) // Check to ensure the list is not NULL.
    {
        if((list->head != NULL) && (list->current != NULL) && (list->tail != NULL))    // Check to ensure the head, current, and tail are not null.
        {
            current_node = list->head;   // Assign the current node to be the head of the list.
            last_node = list->tail;  // Assign the last node to be the tail of the list.

            while(current_node != last_node)   // Check to see if there is more than 1 item in the list.
            {
                next_node = current_node->next; // Save the next node so the information is not lost when the current node is freed.
                free(current_node); // Free the current node.
                current_node = next_node;   // Move to the next node.
            }

            free(current_node); // Free the current node if there is only one node in the list.
            free(list);  // Free the list.
        }
    }

    return; // Return void.
}

/** Inserts at the head of the list.
 *
 * DATA becomes the new head of the list and DATA's successor is the
 * previous head of the list. DATA must not be NULL.
 *
 * The current item is set to DATA.
 *
 * On error the list is not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert(list list, list_data data) // Insert the item data into the head of the list.
{
    struct list_node *new_node; // Initialize a pointer to a new node.
    struct list_node *current_node; // Initialize a pointer for the current node.
    struct h_object_s *new_item;    // Initialize a pointer to a new item.

    if(list != NULL && data != NULL) // Check to ensure that the list and the item are not null.
    {
        new_item = data;    // Assign the data to the new item.
        if((list->head != NULL) && (list->tail != NULL) && (list->current != NULL) )   // Check to ensure that the head, current, and tail are not null.
        {
            if(list->head->item_data == NULL)    // If head of the list is empty.
            {
                /* The head of the list is empty. */
                list->head->item_data = new_item;    // Place the new item at the top of the list.
                list->current = list->head;   // Set the current node to be the head of the list.
                return (list->current->item_data);  // Return the new item.
            }
            else    // If the list is not empty
            {
                /* The head of the list is NOT empty. */
                new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
                if(new_node != NULL)    // Check to make sure that new node is not null.
                {
                    current_node = list->head;   // Set the current node to be the head.
                    new_node->item_data = new_item; // Place the new item in the new node.
                    new_node->next = current_node;  // Link the new node's next to the current node.
                    current_node->prev = new_node;  // Link the current node's prev to the new node.
                    list->current = new_node;    // Set the new node to be the current node.
                    list->head = new_node;   // Set the new node to be the head of the list.

                    return (list->current->item_data);  // Return the new item.
                }
            }
        }
        /* If the list is empty. */
        new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
        new_node->item_data = new_item; // Assign the new item to the new node.
        list->head = new_node;   // Make the new node the head of the list.
        list->current = new_node;    // Make the new node the current node.
        list->tail = new_node;   // Make the new node the tail of the list.

        return (list->current->item_data);  // Return the new item.
    }
    return (NULL); // Return null.
}

/** Appends to the tail of the list.
 *
 * DATA becomes the new tail and DATA's predecessor is the previous
 * tail of the list. DATA must not be NULL.
 *
 * The current item is set to DATA.
 *
 * On error the list is not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_append(list list, list_data data)
{
    struct list_node *new_node; // Initialize a pointer to a new node.
    struct list_node *current_node; // Initialize a pointer for the current node.
    struct h_object_s *new_item;    // Initialize a pointer to a new item.

    if(list != NULL && data != NULL) // Check to ensure that the list and the item are not null.
    {
        new_item = data;    // Assign the data to the new item.
        if((list->head != NULL) && (list->tail != NULL) && (list->current != NULL) )   // Check to ensure that the head, current, and tail are not null.
        {
            if(list->tail->item_data == NULL)    // If the tail of the list is empty.
            {
                /* The head of the list is empty. */
                list->tail->item_data = new_item;    // Place the new item at the top of the list.
                list->current = list->tail;   // Set the current node to be the head of the list.
                return (list->current->item_data);  // Return the new item.
            }
            else    // If the list is not empty
            {
                /* The tail of the list is NOT empty. */
                new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
                if(new_node != NULL)    // Check to make sure that new node is not null.
                {
                    current_node = list->tail;   // Set the current node to be the head.
                    new_node->item_data = new_item; // Place the new item in the new node.
                    new_node->prev = current_node;  // Link the new node's next to the current node.
                    current_node->next = new_node;  // Link the current node's prev to the new node.
                    list->current = new_node;    // Set the new node to be the current node.
                    list->tail = new_node;   // Set the new node to be the head of the list.

                    return (list->current->item_data);  // Return the new item.
                }
            }
        }
        /* If the list is empty. */
        new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
        new_node->item_data = new_item; // Assign the new item to the new node.
        list->head = new_node;   // Make the new node the head of the list.
        list->current = new_node;    // Make the new node the current node.
        list->tail = new_node;   // Make the new node the tail of the list.

        return (list->current->item_data);  // Return the new item.
    }
    return (NULL); // Return null.
}

/** Inserts before the current item.
 *
 * DATA's predecessor will be the current item's predecessor. DATA's
 * successor will be the current item. DATA must not be NULL.
 *
 * The current item becomes DATA.
 *
 * It is an error if the current item is NULL. On error the list is
 * not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert_before(list list, list_data data)
{
    struct list_node *new_node; // Initialize a pointer for a new node.

    if((list != NULL) && (data != NULL) && (list->current != NULL) && (list->current->item_data != NULL)) // Check to ensure that the list, current node, data, and current item are not null.
    {
        new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
        new_node->item_data = data; // Insert the new item into the new node.

        if(new_node != NULL)    // Check to ensure that the new node was successfully created.
        {
            if(list->current != list->head)   // Check to see if the current node is the head of the list.
            {
                /* Current node is NOT the head of the list. */

                /* Assign the links before the new node. */
                list->current->prev->next = new_node;   // Link the previous node to the new node.
                new_node->prev = list->current->prev;   // Link the new node to the previous node.

                /* Assign the links behind the new node. */
                new_node->next = list->current; // Link the new node to the current node.
                list->current->prev = new_node; // Link the current node to the new node.

                return (list->current->item_data);  // Return the current item.
            }
            /* Current node is the head of the list. */

            /* Assign the links behind the new node. */
            new_node->next = list->current; // Link the new node to the current node.
            list->current->prev = new_node; // Link the current node to the new node.

            list->head = new_node;  // Make the new node the new head of the list.

            return (list->current->item_data);  // Return the current item.
        }
    }
    /* List is empty. */
    return (NULL);   // Returns null to indicate an error.
}

/** Inserts after the current item.
 *
 * DATA's predecessor will be the current item. DATA's successor will
 * be the current item's successor.  DATA must not be NULL.
 *
 * The current item becomes DATA.
 *
 * It is an error if the current item is NULL. On error the list is
 * not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert_after(list list, list_data data)
{
    struct list_node *new_node; // Initialize a pointer for a new node.

    if((list != NULL) && (data != NULL) && (list->current != NULL) && (list->current->item_data != NULL)) // Check to ensure that the list, current node, data, and current item are not null.
    {
        new_node = calloc(1,sizeof(struct list_node));  // Allocate memory for a new node.
        new_node->item_data = data; // Insert the new item into the new node.

        if(new_node != NULL)    // Check to ensure that the new node was successfully created.
        {
            if(list->current != list->tail)   // Check to see if the current node is the head of the list.
            {
                /* Current node is NOT the tail of the list. */

                /* Assign the links behind the new node. */
                list->current->next->prev = new_node;   // Link the previous node to the new node.
                new_node->next = list->current->next;   // Link the new node to the previous node.

                /* Assign the links before the new node. */
                new_node->prev = list->current; // Link the new node to the current node.
                list->current->next = new_node; // Link the current node to the new node.

                return (list->current->item_data);  // Return the current item.
            }
            /* Current node is the tail of the list. */

            /* Assign the links behind the new node. */
            new_node->prev = list->current; // Link the new node to the current node.
            list->current->next = new_node; // Link the current node to the new node.

            list->tail = new_node;  // Make the new node the new head of the list.

            return (list->current->item_data);  // Return the current item.
        }
    }
    /* List is empty. */
    return (NULL);   // Returns null to indicate an error.
}

/** Removes the current item from the list.
 *
 * Sets the new current item to the successor of the removed current
 * item. Does nothing if the current item is NULL.
 *
 * Returns the removed item (may be NULL).
 */
list_data list_remove(list list)
{
    struct h_object_s *removed_item;    // Initialize a pointer for the item being removed.
    struct list_node *next_node;    // Initialize a pointer for the next node.
    struct list_node *prev_node;    // Initialize a pointer for the previous node.

    if((list != NULL) && (list->current != NULL) && (list->current->item_data != NULL)) // Check to ensure that the list, current node, and current item are not null.
    {
        removed_item = list->current->item_data;    // Assign the current item in the list to current item.

        next_node = list->current->next; // Assign the current next node to next node.
        prev_node = list->current->prev; // Assign the current previous node to prev node.

        if(list->head != list->tail)  // Check to see if there is only one node in the list.
        {
            if(prev_node != NULL)    // Check to see if the previous node is null (This means the current node is the head of the list).
            {
                if(next_node != NULL)   // Check to see if the next node is null. (This means the current node is the tail of the list).
                {
                    /* Current node is NOT the head or tail. */
                    next_node->prev = prev_node;    // Link previous node to next node.
                    prev_node->next = next_node;    // Link next node to previous node.
                    list->current = next_node;   // Replace current node with next node.

                    return(removed_item);   // Return the removed item.
                }
                /* Current node is the tail of the list. */
                list->current = prev_node;   // Replace the current node with the previous node.
                list->tail = prev_node;  // Replace the tail of the list with the previous node.
                list->current->next = NULL;  // Break the link to the next node.

                return (removed_item);  // Return the removed item.
            }
            /* Current node is the head of the list. */
            list->current = next_node;   // Replace the current node with the next node.
            list->head = next_node;  // Replace the head of the list with the next node.
            list->current->prev = NULL;  // Break the link to the previous node.

            return (removed_item);  // Return the removed item.
        }
        /* Current node is the only node in the list. */
        list->head->item_data = NULL;   // Clear the head of the list.
        list->current->item_data = NULL;    // Clear the current node.
        list->tail->item_data = NULL;   // Clear the tail of the list.

        return (removed_item);  // Return the removed item.
    }
    return (NULL);  // Return null.
}

/** Returns the list head.
 *
 * Sets the current item to the list head or NULL.
 *
 * Returns the list head or NULL if the list is empty.
 */
list_data list_first(list list)  // List_first returns the first item in the list.
{
    if((list != NULL) && (list->head != NULL) && (list->head->item_data != NULL))  // Check to ensure that the list, list head node, and list head item are not null.
    {
        list->current = list->head;   // Assign the head of the list to be the current node in the list.
        return (list->head->item_data);    // Return the first item.
    }
    return (NULL);   // Return null.
}

/** Moves the current item forward in the list.
 *
 * Sets the new current item to the successor of the current item. If
 * the current item is the list tail or the current item is NULL then
 * the new current item is NULL.
 *
 * Returns the new current item.
 */
list_data list_next(list list)   // List_next moves the current item forward  to the next item in the list.
{
    struct h_object_s *next_item;    // Declare a pointer for the next item.
    struct list_node *current_node; // Declare a pointer for the current node.

    if((list != NULL) && (list->current != NULL) && (list->current->item_data != NULL))    // Check to ensure that the list, current node, and current item are not null.
    {
        current_node = list->current;    // Assign the current node from the list to be current node.

        if((current_node != list->tail) && (current_node->next != NULL))   // Check to ensure the current node is not the tail and the next node is not null.
        {
            current_node = current_node->next;  // Assign the current node to be the next node.
            next_item = current_node->item_data;    // Assign the current item to next item.
            list->current = current_node;    // Assign the current node in the list to be current node.
            return (next_item); // Return the next item.
        }
    }

    return (NULL);  // Return null.
}

/** Moves the current item backward in the list.
 *
 * Sets the new current item to the predecessor of the current
 * item. If the current item is the list head or the current item is
 * NULL then the new current item is NULL.
 *
 * Returns the new current item.
 */
list_data list_prev(list list)
{
    struct h_object_s *previous_item;    // Declare a pointer for the previous item.
    struct list_node *previous_node; // Declare a pointer for the current node.

    if((list!=NULL) && (list->current != NULL) && (list->current->item_data!= NULL))   // Check to ensure that the list, current node, and current item are not null.
    {
        if((list->current->prev != NULL) && (list->current->prev->item_data != NULL)) // Check to ensure that the previous node and previous item are not null.
        {
            previous_node = list->current->prev;  // Assign the previous node from the list to previous node.
            previous_item = previous_node->item_data;    // Assign the previous node's item data to previous item.
            list->current = previous_node;   // Assign the previous node to be the current node.
            return (previous_item); // Return the previous item.
        }
    }
    return (NULL);  // Return a null pointer.
}

/** Returns the list tail.
 *
 * Sets the current item to the list tail or NULL.
 *
 * Returns the list tail or NULL if the list is empty.
 */
list_data list_last(list list)   // Sets the current item to be the tail of the list.
{
    struct h_object_s *last_item;  // Declare a pointer  for the last item.

    if((list!=NULL) && (list->tail!=NULL) && (list->tail->item_data!=NULL))    // Check to ensure that the list, list tail, and list tail item are not null.
    {
        last_item = list->tail->item_data;   // Assign the item in the tail of the list to last item.
        list->current = list->tail;  // Assign the tail of the list to be the current node of the list.
        return (last_item); // Return the last item.
    }
    return (NULL);  // Return null.
}

/** Returns the current item of the list.
 *
 * Returns the current item of LST (may return NULL).
 */
list_data list_curr(list list)   // Returns the current item in the list.
{
    struct h_object_s *current_item;    // Declare a pointer for the current item.

    if((list!=NULL) && (list->current!=NULL)) // Check to ensure that the list and the current node are not null.
    {
        current_item = list->current->item_data; // Assign the current item in the list to current item.
        return (current_item);  // Return the current item.
    }
    return (NULL);  // Return null.
}
