/**
 * hashDictionary.c
 *
 * Implements a dictionary using an external hash table
 *
 * Created by Sally Goldin 1 April 2013 as a sample solution for
 *   CPE113 Lab 10
 *   
 *   Modified 27 March 2017 to change bucket count to prime number
 * Adapted for AiCE WARP 15 July 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chainedHashTable.h"

#define BUCKET_COUNT 53

/* Structure to store one word with its definition */
/* This will be the data we store in the hash table */
typedef struct
{
    char word[64];      /* word we want to store */
    char definition[1024];  /* definition */
} DICT_ENTRY_T;
 

/* Read word file and construct the dictionary.
 * Arguments
 *  pFile      -  file pointer for reading, assumed open and checked.
 * Returns 1 if successful, 0 for allocation failure or read error.
 */
int buildDictionary(FILE* pFile)
{
   char input[512];      /* buffer to store word and definition from file */
   char* pDelim = NULL;  /* used to find position of '|' */
   DICT_ENTRY_T * pEntry = NULL;
   int returnVal = 1;
   int wordCount = 0;
   while ((fgets(input,sizeof(input),pFile) != NULL) &&
           (returnVal == 1))  
   {
      int len = strlen(input);
      if (input[len-1] == '\n')
      {
         input[len-1] = '\0';    /* get rid of newline */
      }
      pDelim = strpbrk(input,"|");  /* find the vertical bar */
      if (pDelim != NULL)           /* if no delim, just skip the line */
      {
         *pDelim = '\0';              /* replace ':' with 0 */
         pEntry = (DICT_ENTRY_T*) calloc(1,sizeof(DICT_ENTRY_T));
         if (pEntry == NULL) /* allocation error */
         {
            returnVal = 0;
            break; /* this is not a recoverable error so exit */
         }
         *pDelim = '\0'; /* replace delimiter with a terminator */
         strcpy(pEntry->word,input);  /* copy the word */
         strcpy(pEntry->definition,(pDelim+1)); /* copy the definition */
         /* Put the entry into the dictionary */
         returnVal = hashTableInsert(pEntry->word,pEntry);
         if (!returnVal)  /* success */
         {
            printf("Error inserting %s into hash table\n", pEntry->word);
            break;
         }
         wordCount++;
      }  /* if no delimiter, just skip the line */
   }
   printf("Stored %d words in the dictionary\n",wordCount);
   return returnVal;
}

/* print the definitions for a word, or print 'Not Found'
 * if not in the dictionary. 
 * Arguments 
 *   word          -   Word to look up
 */
void printDefinition(char* word)
{
   DICT_ENTRY_T* pWord = NULL;
   printf("\n");
   pWord = (DICT_ENTRY_T*) hashTableLookup(word);
   if (pWord == NULL)
   {
      printf("Word '%s' not found in the dictionary\n",word);
   }
   else
   {
      int i;
      printf("Word: %s \n",pWord->word);
      printf("Definition: %s\n",pWord->definition); 
   }
   printf("\n");
}  


int main(int argc, char* argv[])
{

   FILE * pFp = NULL;           /* used to read input file */
   int status = 0;              /* for function return values */
   pFp = fopen("wordlist.txt","r");
   if (pFp == NULL)
   {
      printf("Error - cannot open file 'wordlist.txt'\n");
      exit(1);
   } 
   /* initialize the hash table */
   status = hashTableInit(BUCKET_COUNT);
   if (!status)
   {
      printf("Error initializing hash table\n");
      exit(1);
   }
   status = buildDictionary(pFp);
   fclose(pFp);
   if (!status)
   {
      printf("Allocation error building dictionary\n");
      exit(1);
   } 
   /* now loop, allowing lookup or addition of new words */
   while (1)
   {
      int option = 0;
      char input[64];
      char word[64];
      printf("\nAvailable operations: \n");
      printf("\t1 - Look up a word in the dictionary\n");
      printf("\t2 - Add a word to the dictionary\n");
      printf("\t3 - Add an additional definition to an existing word\n");
      printf("\t4 - Exit the program\n");
      printf("Option? ");
      fgets(input,sizeof(input),stdin);
      sscanf(input,"%d",&option);
      if (option == 1) 
      {
         printf("Find definition for what word ('EXIT' to exit)? ");
         fgets(input,sizeof(input),stdin);
         memset(word,0,sizeof(word));
         sscanf(input,"%s",word);
         printDefinition(word);
      }    
      else if (option == 2)
      {
         printf("FOR IMPLEMENTATION BY THE STUDENT!\n");
         // STUDENT TASK ONE
         // Add code here to ask for word and definition, then
         // add to the dictionary
      }
      else if (option == 3)
      {
         printf("FOR IMPLEMENTATION BY THE STUDENT!\n");
         // STUDENT TASK TWO
         // Add code here to add an additional definition to an existing
         // word. NOTE you may need to modify the structure of
         // DICT_ENTRY_T in order to complete this task
      }
      else if (option == 4)
      {
         break;
      }
      else 
      {
         printf("Please enter a value between 1 and 4!\n");
      }
   }
   /* free the hash table before we exit */
   hashTableFree();
}
