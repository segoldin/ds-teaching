/* 
 * chainedHashTable.c
 *
 * Implementation of abstractHashTable.h that uses a chained
 * hash table. The calling program supplies the hashing function
 * as part of the initialization.
 *
 * Limitation: this implementation will not work well for duplicate
 * keys. It will store both but the returned data is unpredictable.
 *
 * Limitation: this implementation assumes keys are strings 
 * less than 128 chars long
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chainedHashTable.h"

#define KEYLEN 128

/* Structure for table elements */
typedef struct _hashItem
{
    char key[KEYLEN];		/* copy of the key */
    void *data;			/* data */
    struct _hashItem *next;	/* next item in the bucket if any */
} HASH_ITEM_T;

/* Structure for list with head and tail */
typedef struct _linkedList
{
    HASH_ITEM_T *head;		/* first item in list - null if list empty */
    HASH_ITEM_T *tail;		/* last item in the list */
} LINKED_LIST_T;


/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char *key)
{
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
    {
	/* shift up four bits then add in next char */
	result = (result << 4) + key[i];
	if (tmp = (result & 0xf0000000))	/* if high bit is set */
	{
	    /* XOR result with down shifted tmp */
	    result = result ^ (tmp >> 24);
	    /* then XOR with tmp itself */
	    result = result ^ tmp;
	}
    }
    result = result % size;	/* make it fit in the table size */
    return result;
}


/* Hash function - set by hashTableInit  */
unsigned int (*hashFn) (char *key) = NULL;

static LINKED_LIST_T *table = NULL;	/* we will allocate our table based on
					 * initialization arguments and store it
					 * here 
					 */
static int tableSize = 0;	/* size of the table */
static int itemCount = 0;	/* keep track of current number of stored items */

/* Return the number of slots in the hash table.
 */
int hashTableSize()
{
    return tableSize;
}


/* Return the number of items currently stored in the hash table.
 */
int hashTableItemCount()
{
    return itemCount;
}

/* Initialize the hash table.
 * Arguments
 *    size                - How many slots in the table
 *                          Must be 1 or greater. We assume the caller
 *                          has checked this.
 * Return 1 if successful, 0 if some error occurred.
 */
int hashTableInit(int size)
{
    int bOk = 1;
    /* free the old table, if any */
    hashTableFree();
    hashFn = bitwiseOpHash;
    tableSize = size;
    /* try to allocate the table, which will store pointers
     * to LINKED_LIST_T elements.
     */
    table = (LINKED_LIST_T *) calloc(size, sizeof(LINKED_LIST_T));
    if (table == NULL)
    {
	bOk = 0;
    }
    return bOk;
}


/* Free the hash table.
 */
void hashTableFree()
{
    int i = 0;
    HASH_ITEM_T *pItem = NULL;
    HASH_ITEM_T *pNextItem = NULL;
    if (table != NULL)
    {
	for (i = 0; i < tableSize; i++)
	{
	    if (table[i].head != NULL)	/* something stored in this slot */
	    {
		pItem = table[i].head;
		/* walk the linked list, freeing each item */
		while (pItem != NULL)
		{
		    pNextItem = pItem->next;
		    free(pItem);
		    pItem = pNextItem;
		}
		table[i].head = NULL;
		table[i].tail = NULL;
	    }
	}
	free(table);
	table = NULL;
	tableSize = 0;
	itemCount = 0;
    }
}


/* Insert a value into the hash table.
 * Arguments 
 *    key                 - character string key
 *    data                - data to store in the table
 * Returns true (1) unless hash table has not been initialized or
 * we can't allocate memory, in which case returns false (0)
 */
int hashTableInsert(char *key, void *data)
{
    int bOk = 1;
    int hashval = 0;
    HASH_ITEM_T *pItem = NULL;
    HASH_ITEM_T *pTemp = NULL;
    if (table == NULL)		/* not initialized */
	return 0;
    pItem = (HASH_ITEM_T *) calloc(1, sizeof(HASH_ITEM_T));
    if (pItem == NULL)
    {
	bOk = 0;		/* can't allocate memory */
    }
    else
    {
	strncpy(pItem->key, key, KEYLEN - 1);
	pItem->data = data;
	hashval = hashFn(key);
	if (table[hashval].head == NULL)
	{
	    table[hashval].head = pItem;	/* bucket was empty */
	}
	else
	{
	    /* put the new item at the end of the bucket list */
	    table[hashval].tail->next = pItem;
	}
	table[hashval].tail = pItem;
	itemCount++;
    }
    return bOk;
}


/* Remove a value from the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data removed, or NULL if it is not found or table not init'd 
 */
void *hashTableRemove(char *key)
{
    void *foundData = NULL;
    HASH_ITEM_T *pPrev = NULL;
    HASH_ITEM_T *pTemp = NULL;
    if (table != NULL)		/* initialized */
    {
	int hashval = hashFn(key);
	if (table[hashval].head != NULL)	/* in the table */
	{
	    pTemp = table[hashval].head;
	    while (pTemp != NULL)
	    {
		if (strncmp(pTemp->key, key, KEYLEN - 1) == 0)	/* match */
		{
		    foundData = pTemp->data;
		    if (pPrev == NULL)	/* first item */
		    {
			table[hashval].head = pTemp->next;
		    }
		    else
		    {
			pPrev->next = pTemp->next;
		    }
		    /* adjust tail if necessary */
		    if (table[hashval].tail == pTemp)
		    {
			table[hashval].tail = pPrev;
		    }
		    free(pTemp);
		    itemCount--;
		    pTemp = NULL;	/* this will make us exit loop */
		}
		else
		{
		    pPrev = pTemp;
		    pTemp = pTemp->next;	/* check next item */
		}

	    }			/* end loop through items in the bucket */
	}			/* end if the bucket is not empty */
    }				/* end if the hash table is initialized */
    return foundData;
}


/* Look up a value in the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data associated with the key, or NULL if 
 * data associated with the key is not found.
 */
void *hashTableLookup(char *key)
{
    /* This function is similar to remove but we do not
     * change anything in the hashtable structure 
     */
    void *foundData = NULL;
    HASH_ITEM_T *pPrev = NULL;
    HASH_ITEM_T *pTemp = NULL;
    if (table != NULL)		/* initialized */
    {
	int hashval = hashFn(key);
	if (table[hashval].head != NULL)	/* in the table */
	{
	    pTemp = table[hashval].head;
	    while (pTemp != NULL)
	    {
		if (strncmp(pTemp->key, key, KEYLEN - 1) == 0)	/* match */
		{
		    foundData = pTemp->data;
		    pTemp = NULL;	/* this will make us exit loop */
		}
		else
		{
		    pPrev = pTemp;
		    pTemp = pTemp->next;	/* check next item */
		}
	    }			/* end loop through items in the bucket */
	}			/* end if the key is in the table */
    }				/* end if the hash table is initialized */
    return foundData;
}
