
/*
 *  treeSort.c
 *
 *  Read a set of strings from a text file and
 *  insert in a sorted binary tree structure.
 *  Then read them back in sorted order
 *
 *  Created by Sally Goldin, 27 October 2011 for CPE113
 *  Modified 4 December 2016 to make comments more accurate
 *    and allow the tree to free the data copies.
 *  Modified 15 January 2020 to add trimString() function.
 *  Modified 21 January 2021 to actually use trimString!
 *            Change time reporting to use double
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "binaryTree.h"
#include "timeFunctions.h"

void writeArray(char *array[],int count, int maxsize, char* outputFilename);
void printArray(char *array[], int count);
void freeAll(char* data[], TREE_T* binTree);
void trimString(char* string); 

/*
 * Main function. 
 * Reads first line of file to control allocation.
 * Allocates array and reads from the file. Then sorts
 * the strings and writes them to another file.
 */
int main(int argc, char* argv[])
{
    char inputLine[128];  /* buffer for reading file data */
    char ** data = NULL;   /* This will become our array */
    FILE* pInfile = NULL; /* File pointer for input file */
    int count = 0;        /* number of lines/names in file */
    int maxsize = 0;      /* Length of longest string */
    int i = 0;            /* Loop counter */
    unsigned long interval = 0; /* measure time required to sort */
    /* Input and output filenames as specified by the user */
    char inputFile[128]; 
    char outputFile[128];
    TREE_T * binTree = NULL;   /* handle for the tree */

    /* check to make sure we have the right number of arguments */
    if (argc != 3)
       {
       fprintf(stdout,"Wrong number of arguments! Correct usage: \n");
       fprintf(stdout,"  ./treeSort [inputfilename] [outputfilename]\n");
       exit(1);
       }
    /* Copy files from argument array to local variables */
    strcpy(inputFile,argv[1]); 
    strcpy(outputFile,argv[2]);

    /* Try to open the input file */
    pInfile = fopen(inputFile,"r");
    /* Check that the open succeeded */
    if (pInfile == NULL)
       {
       fprintf(stderr,"Unable to open file '%s'\n",inputFile);
       exit(1);
       }
    /* Read the first line in the file so we know what to allocate */
    if (fgets(inputLine,sizeof(inputLine),pInfile) == NULL)
       {
       fprintf(stderr,"Input file seems to be empty\n");
       exit(2);
       }
    sscanf(inputLine,"%d %d",&count,&maxsize);
    if ((count == 0) || (maxsize == 0))
       {
       fprintf(stderr,"Input file does not have expected format\n");
       exit(3);
       }
    fprintf(stdout,
      "Input file %s contains %d items to sort\n",inputFile,count);
    /* If we get this far, we can do the allocation */
    data = calloc(count,sizeof(char*)); 
           /* this will be an array of pointers to characters */
           /* each value will be allocated separately using strdup */        
    if (data == NULL)
       {
       fprintf(stderr,"Memory allocation error allocating array\n");
       exit(4);
       }
    /* Create a tree */
    binTree =  createTree();
    if (binTree == NULL)
       {
       fprintf(stderr,"Memory allocation error allocating tree\n");
       exit(5);
       }
    /* Read the data. As we read each string, call insertItem()
     * to insert it in the tree.
     * We don't save it in the array yet. 
     */    
    for (i = 0; i < count; i++)
      {
      int len = 0;
      if (fgets(inputLine,sizeof(inputLine),pInfile) == NULL)
	 {
         fprintf(stderr,"Unexpected end of file!\n");
	 exit(6);  
	 } 
      /* get rid of newline then store */
      trimString(inputLine);
      /* now insert it in the tree */
      recordTime(1);  /* the time should include both building the
                       * tree and retrieving the values 
                       */
      if (!insertItem(binTree,inputLine))
	 {
         fprintf(stderr,"Memory allocation error putting data in the tree\n");
         exit(8);
	 }
      interval += recordTime(0);
      }
    fclose(pInfile);
    /* Now get the sorted data */
    recordTime(1);
    retrieveSortedData(binTree,data);
    interval += recordTime(0);
    fprintf(stdout,
          "Sorting %d items required %ld microseconds\n",count,interval);
    double perItem = ((double) interval) / count;
    if (perItem > 0.0)
        fprintf(stdout,"(%.2lf microseconds per item)\n",perItem);
    else 
        fprintf(stdout,"(less than 1 microsecond per item)\n");
    /* Write the sorted array to a file */
    writeArray(data,count,maxsize,outputFile);
    freeAll(data,binTree);
}



/*
 * Output the values stored in the array to a text file with
 * the same format as the input file
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 *     maxsize  - max length of each data item in chars
 *     outputFilenam - name of output file
 */
void writeArray(char *array[],int count, int maxsize, char* outputFilename)
{
    int i ;
    FILE* pOutfile = NULL;
    /* open output file */
    pOutfile = fopen(outputFilename,"w");
    if (pOutfile != NULL)
       { 
       fprintf(pOutfile,"%d %d\n", count,maxsize);
       for (i = 0; i < count; i++)
	  {
	  fprintf(pOutfile,"%s\n",array[i]);
          } 
       fclose(pOutfile); /* Very important to close output files */
       }
    else
       {
       fprintf(stderr,"Error - cannot open output file %s\n",outputFilename);
       }
}

/*
 * Print the values stored in the array to the screen
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 */
void printArray(char *array[],int count)
{
    int i ;
    fprintf(stdout,"Current contents of the array\n");
    for (i = 0; i < count; i++)
      {
      fprintf(stdout,"%s\n",array[i]);
      } 
}

/* Free a dynamically allocated array of char* values.
 * Free the individual strings first, then the array itself 
 * Arguments 
 *    data  - array of char* elements
 *    binTree - tree allocated by createTree
 */
void freeAll(char* data[], TREE_T* binTree)
{
    int i;
    freeTree(binTree);
    free(data);
}

/* removes all whitespace (including \n, \r) from the end of
 * the passed string 'string'
 */
void trimString(char * string)
{
    int i = strlen(string) - 1;
    while (i >= 0)
      {
      if (isspace(string[i]))
	{
	string[i] = '\0';
	i--;
	} 
      else
        break;
      }
}
