/*
 *  stringBubble.c
 *
 *  Read a set of strings from a text file into a
 *  dynamically allocated array, sort the array using bubble sort
 *  and then write it to another text file. The original file
 *  includes a count of the number of strings and the maximum
 *  string size in the first line. 
 *
 *  Created by Sally Goldin, 27 October 2011 for CPE113
 *            Updated 6 Jan 2016 for CPE111
 *            Updated 18 Jan 2018 to use function instead of macro
 *            Updated 15 Jan 2020 to add trimString function (to work for
 *                  both Windows and Linux line termination)
 *            Updated on 21 Jan 2021 to change time reporting to use double
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "timeFunctions.h"


void swapStrings(char* string1, char* string2);
void sortArray(char *array, long int count);
void writeArray(char *array,long int count,char* outputFilename);
int readArray(char *array, long int count,FILE* pFp);
unsigned long recordTime(int bStart);
char* getStringPointer(char *array, int i);
void trimString(char* string); 

/* Global variables */
/* Set once, never changed -- needed for getStringPointer() */
int maxsize = 0;      /* Length of longest string */

/*
 * Main function. 
 * Reads first line of file to control allocation.
 * Allocates array and reads from the file. Then sorts
 * the strings and writes them to another file.
 */
int main(int argc, char* argv[])
{
    char inputLine[128];  /* buffer for reading file data */
    long int count = 0;   /* number of lines/names in file */
    FILE* pInfile = NULL; /* File pointer for input file */
    unsigned long interval = 0; /* measure time required to sort */
    char * data = NULL;   /* This will become our array */
    /* Input and output filenames as specified by the user */
    char inputFile[128]; 
    char outputFile[128];

    /* check to make sure we have the right number of arguments */
    if (argc != 3)
       {
       fprintf(stdout,"Wrong number of arguments! Correct usage: \n");
       fprintf(stdout,"  ./stringBubble [inputfilename] [outputfilename]\n");
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
    fprintf(stdout,"Input file %s contains %d items to sort\n",inputFile,count);
    /* If we get this far, we can do the allocation */
    data = calloc(count,maxsize); /* sizeof char is always 1 */        
    if (data == NULL)
       {
       fprintf(stderr,"Memory allocation error\n");
       exit(4);
       }
    /* Read the data. This function returns 0 if an error occurs */    
    if (!readArray(data,count,pInfile))
       {
       fprintf(stderr,"Error reading information from file\n");
       fclose(pInfile);
       free(data);
       exit(5);
       }
    fclose(pInfile);
    /* Sort the array*/
    recordTime(1);
    sortArray(data,count);
    interval = recordTime(0);
    fprintf(stdout,
          "Sorting %d items required %ld microseconds\n",count,interval);
    double perItem = ((double) interval) / count;
    if (perItem > 0.0)
        fprintf(stdout,"(%.2lf microseconds per item)\n",perItem);
    else 
        fprintf(stdout,"(less than 1 microsecond per item)\n");
    /* Write the sorted array to a file */
    writeArray(data,count,outputFile);
    free(data);
}

/* returns a pointer to the beginning of the ith string. */
char* getStringPointer(char* array,int i)
{
   /* each string is 'maxsize' chars long
    * 'maxsize' is global for convenience.
    * To get to string 'i' we need to skip i * maxsize chars.
    */
   return (char *) &array[i * maxsize];
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

/*
 * Read the contents of the file into the array.
 * Each line is treated as a single item. 
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 *     maxSize  - max length of each data item in chars
 *     pFp      - file pointer for open input file 
 * Returns 1 for success, 0 if some read error (e.g. not enough
 * lines in the file
 */
int readArray(char *array, long int count, FILE* pFp)
{
    char inputLine[128];  /* buffer for reading file data */
    int i;                /* loop counter */
    int bOk = 1;          /* return status */
    int len = 0;          /* for string length */ 
    for (i = 0; i < count; i++)
      {
      if (fgets(inputLine,sizeof(inputLine),pFp) == NULL)
	 {
	 bOk = 0;  /* File does not have expected num of lines */
	 break;  
	 } 
      /* get rid of newline then store */
      trimString(inputLine);
      strcpy(getStringPointer(array,i),inputLine);
      }
    return bOk;
}

/*
 * Sort the array 'array' into ascending
 * order using the BubbleSort algorithm.
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 *     maxSize  - max length of each data item in chars
 */
void sortArray(char *array, long int count)
{
    long int i;
    long int swapCount = 1;
  
    while (swapCount > 0)
       {
       swapCount = 0;
       for (i = 0; i < count-1; i++)
           {
	   /* if item[i] should be later than item [i+1] */
	     if (strcmp(getStringPointer(array,i), 
		        getStringPointer(array, i+1)) > 0) 
	       {
	       swapStrings((getStringPointer(array,i)), 
			   (getStringPointer(array,i+1)));
	       swapCount = swapCount + 1;
	       }
	   }    
       }
}

/* Swap the contents of two strings.
 * Arguments  string1  - First string
 *            string2  - Second string.
 * Upon return, string1 will hold the previous
 * contents of string2 and vice versa.
 * Both strings are assumed to have the same
 * maximum size which is < 128.
 */
void swapStrings(char* string1, char* string2)
{
    char temp[128];
    strcpy(temp,string1);
    strcpy(string1,string2);
    strcpy(string2,temp);
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
void writeArray(char *array,long int count,char* outputFilename)
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
	  fprintf(pOutfile,"%s\n",(getStringPointer(array,i)));
          } 
       fclose(pOutfile); /* Very important to close output files */
       }
    else
       {
       fprintf(stderr,"Error - cannot open output file %s\n",outputFilename);
       }
}



