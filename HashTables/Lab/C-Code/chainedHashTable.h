/* 
 *   chainedHashTable.h
 *
 *   Header file for a hash table that uses strings as keys
 *   and stores pointers to arbitrary structures as values
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */
#ifndef CHAINEDHASHTABLE_H
#define CHAINEDHASHTABLE_H

/* Return the number of slots in the hash table.
 */
int hashTableSize();

/* Return the number of items currently stored in the hash table.
 */
int hashTableItemCount();


/* Initialize the hash table.
 * Arguments
 *    size                - How many slots in the table
 *                          Must be 1 or greater. We assume the caller
 *                          has checked this.
 * Returns 1 if successful, 0 if some error occurred.
 */
int hashTableInit(int size);


/* Free the hash table.
 */
void hashTableFree();


/* Insert a value into the hash table.
 * Arguments 
 *    key                 - character string key
 *    data                - data to store in the table
 * Returns true (1) unless hash table has not been initialized or
 * we can't allocate memory, in which case returns false (0)
 */
int hashTableInsert(char* key, void* data);


/* Remove a value from the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data removed, or NULL if it is not found or table not init'd .
 */
void* hashTableRemove(char* key);


/* Look up a value in the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data associated with the key, or NULL if 
 * data associated with the key is not found.
 */
void* hashTableLookup(char* key);


#endif
