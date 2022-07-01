/* 
 *  filesearch.c
 *
 *  Functions to return list of files in a directory.
 *  These functions depend on Unix/Posix capabilities and
 *  may not work on Windows. If they do, they will only work
 *  with MinGW or CodeBox which use the Windows port of GCC.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* memcpy */
#include <limits.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "filesearch.h"

static glob_t globbuf;
static char **pFileNameList = NULL;
static int lastCount = 0;	/* keep track of the number of 
				 * elements in the last allocated
				 * file name list so we can do the
				 * free
				 */


/* Free the list of file names allocatd by the previous
 * call to getFileList.
 * Arguments
 *     fileList        List to free
 *     count           Number of entries in the list
 * NOTE - because this function is declared 'static', it
 * cannot be seen outside this module.
 */
static void freeFileList(char **fileList, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
	free(fileList[i]);
    }
    free(fileList);
}


/* Given a pathname plus filename string,
 * returns the part after the last separator.
 * which is assumed to be the node plus extension.
 * Tests for the Unix/Linux separator only.
 * Arguments
 *   pczInputFile     Filename with path
 * Returns filename without path 
 * (actually, a pointer into the input buffer).
 */
char *stripPath(char *pczInputFile)
{
    char *nodeStart = &pczInputFile[strlen(pczInputFile) - 1];
    while ((nodeStart > pczInputFile) && (*nodeStart != '/'))
	nodeStart--;
    if (*nodeStart == '/')
	nodeStart++;
    return nodeStart;
}

/*  Finds and returns a list of the names of files in a directory.
 *  Arguments
 *      directory      Full path name of the directory - no terminating /
 *      pCount         Pointer to integer for returning number of files found
 *                     Returns -1 if an error occurred.
 *  Returns dynamically allocated array of dynamically allocated
 *  strings with full file names including the path. This array
 *  should be freed with freeFileList before the next call
 *  to getFileList. If no files found or an error occurred, returns
 *  NULL. Check value stored in pCount to determine which.
 */
char **getFileList(const char *directory, int *pCount)
{
    int globStat;
    int i = 0;
    char pattern[PATH_MAX];
    *pCount = 0;
    if (pFileNameList != NULL)
	freeFileList(pFileNameList, lastCount);
    lastCount = 0;
    pFileNameList = NULL;
    globbuf.gl_offs = 0;
    strcpy(pattern, directory);
    strcat(pattern, "/*");
    globStat = glob(pattern, 0, NULL, &globbuf);
    if (globStat == 0)
    {
	*pCount = globbuf.gl_pathc;
	if (*pCount > 0)
	{
	    pFileNameList = (char **) calloc(*pCount, sizeof(char **));
	    if (pFileNameList != NULL)
	    {
		for (i = 0; i < *pCount; i++)
		    pFileNameList[i] = strdup(globbuf.gl_pathv[i]);
		lastCount = *pCount;
	    }
	    else
	    {
		printf("Allocation failed in building file list\n");
		*pCount = -1;
	    }
	}
    }
    else if (globStat == GLOB_ABORTED)
    {
	printf("Read error in building file list\n");
	*pCount = -1;
    }
    else if (globStat == GLOB_NOSPACE)
    {
	printf("Not enough memory to build file list\n");
	*pCount = -1;
    }
    return pFileNameList;
}

/* Check to see if a filename is a directory.
 * Arguments
 *    filename           Name of file with full path
 * Returns 1 if this file is a directory, 0 if not.
 */
int isDirectory(const char *filename)
{
    int bDirectory = 0;
    struct stat buffer;
    stat(filename, &buffer);
    unsigned int mode = buffer.st_mode;
    if ((mode & S_IFMT) == S_IFDIR)
	bDirectory = 1;
    return bDirectory;
}

/*  Free any memory associated with the global 
 *  file list, and set the pointer to null.
 */
void cleanupList()
{
    if (pFileNameList != NULL)
    {
	freeFileList(pFileNameList, lastCount);
	pFileNameList = NULL;
    }
}
