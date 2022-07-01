/*
 *  directoryTree.c
 *
 *  Create a tree structure that represents the contents
 *  of a directory and all its subdirectories
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "filesearch.h"

#ifdef MSWINDOWS
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif

typedef struct _fileEntry
{
    char filename[128];		/* name of file or directory -
				 * without path */
    int bDirectory;		/* If true, this is a directory, 
				 * else regular file*/
    int childCount;		/* used to index into child array */
    int level;			/* keep track of how far down the tree 
				 * we are. The root is level 0 
				 */
    struct _fileEntry **childFiles;	/* Dynamically allocated array of files */
    /* Will be null if this file is 
     * NOT a directory 
     */
    struct _fileEntry *pParent;	/* pointer back to the parent node */
} FILE_ENTRY_T;


FILE_ENTRY_T *pRootDirectory = NULL;

/* Free list of strduped filenames
 * Arguments
 *    newFiles    - ptr to array of char* values
 *    fileCount   - size of the array
 */
void freeLocalFileList(char **newFiles, int fileCount)
{
    int i = 0;
    for (i = 0; i < fileCount; i++)
    {
	if (newFiles[i] != NULL)
	    free(newFiles[i]);
    }
    free(newFiles);
}

/* Factorization. Make a local copy of the list returned from
 * getFileList.
 *
 * We have to do this because the original data
 * will be freed in the next (recursive) call to getFileList
 * Arguments
 *    pFiles    -  List to copy
 *    fileCount -  Number of items in the list
 * Returns new list - free with 'freeLocalFileList'
 * Returns NULL for allocation error
 */
char **copyFileList(char **pFiles, int fileCount)
{
    int i = 0;
    char **newFiles = (char **) calloc(fileCount, sizeof(char *));
    if (newFiles != NULL)
    {
	for (i = 0; i < fileCount; i++)
	{
	    newFiles[i] = strdup(pFiles[i]);
	    if (newFiles[i] == NULL)
	    {
		freeLocalFileList(newFiles, fileCount);
		newFiles = NULL;
		break;
	    }
	}
    }
    return newFiles;
}

/** Recursive function to add files from a directory to the
 * file tree.
 * Arguments
 *    pParent    -  parent to which files will be added
 *    filename   -  filename to be added to the tree
 * Return 1 unless there's a memory allocation error, then 0
 */
int buildTree(FILE_ENTRY_T *pParent, char *filename)
{
    char **pFiles = NULL;
    int fileCount = 0;
    int i = 0;
    int bOk = 1;
    FILE_ENTRY_T *pNewNode = NULL;
    pNewNode = (FILE_ENTRY_T *) calloc(1, sizeof(FILE_ENTRY_T));
    if (pNewNode == NULL)
    {
	printf("Error allocating new tree node for file '%s'\n", filename);
	bOk = 0;
    }
    else
    {
	strcpy(pNewNode->filename, stripPath(filename));
	if (isDirectory(filename))
	    pNewNode->bDirectory = 1;	/* otherwise will be 0 from calloc */
	if (pParent == NULL)	/* root */
	{
	    pRootDirectory = pNewNode;
	    pNewNode->pParent = NULL;
	    pNewNode->level = 0;
	}
	else
	{
	    pNewNode->pParent = pParent;
	    pParent->childFiles[pParent->childCount] = pNewNode;
	    pParent->childCount += 1;
	    pNewNode->level = pParent->level + 1;
	}
    }
    /* Now see if this is a directory, and if so, process its contents */
    if ((bOk) && (pNewNode->bDirectory))
    {
	pFiles = getFileList(filename, &fileCount);
	if (fileCount < 0)
	{
	    printf("Error getting list of files in directory '%s'\n",
		   filename);
	    bOk = 0;
	}
	else
	{
	    char **newFiles = copyFileList(pFiles, fileCount);
	    if (newFiles != NULL)
	    {
		pNewNode->childFiles = (FILE_ENTRY_T **)
		    calloc(fileCount, sizeof(FILE_ENTRY_T *));
		if (pNewNode->childFiles == NULL)
		{
		    printf
			("Error allocating child array for directory '%s'\n",
			 filename);

		    bOk = 0;
		}
		else
		{
		    for (i = 0; (i < fileCount) && (bOk); i++)
		    {
			bOk = buildTree(pNewNode, newFiles[i]);
		    }
		}
		/* Free the local copy of the data */
		freeLocalFileList(newFiles, fileCount);
	    }
	}
    }
    return bOk;
}

/* Recursive function to do a depth first traversal
 * of the tree, printing the contents of each node.
 * Arguments
 *   pRoot  - Root node of current subtree to print
 */
void printTree(FILE_ENTRY_T *pRoot)
{
    char indent[128] = "";
    int i = 0;
    for (i = 0; i < pRoot->level; i++)
	strcat(indent, ">");
    printf("%s %s\n", indent, pRoot->filename);
    if (pRoot->bDirectory)
    {
	for (i = 0; i < pRoot->childCount; i++)
	    printTree(pRoot->childFiles[i]);
    }
}


/* Given a FILE_ENTRY_T in the tree, construct a string
 * with the full pathname by going backwards up the tree, following
 * the pParent pointers.
 * Argument 
 *    pTreeNode    -  Tree node that we want the full path for
 * Returns a pointer to a string which holds the full path.
 * This string is static and should be strduped if the user plans
 * to call getFullPath again before using it.
 * BUT can return NULL if allocation of the stack fails. 
 */
char *getFullPath(FILE_ENTRY_T *pTreeNode)
{
    int topStack = 0;
    int i = 0;
    static char fullName[PATH_MAX];	/* assume we won't have anything longer */
    FILE_ENTRY_T *pFromNode = NULL;
    FILE_ENTRY_T **stack =
	calloc(pTreeNode->level + 1, sizeof(FILE_ENTRY_T *));
    if (stack == NULL)
	return NULL;
    stack[topStack] = pTreeNode;
    topStack++;
    pFromNode = pTreeNode->pParent;
    while (pFromNode != NULL)
    {
	stack[topStack] = pFromNode;
	topStack++;
	pFromNode = pFromNode->pParent;
    }
    /* Okay, now pop off the stack to construct the full path */
    memset(fullName, 0, sizeof(fullName));
    for (i = topStack - 1; i >= 0; i--)
    {
	if (i != topStack - 1)
	    strcat(fullName, SEPARATOR);
	strcat(fullName, stack[i]->filename);
    }
    free(stack);
    return fullName;
}

/* Look for a file that matches the passed filename,
 * and if found, print its full path.
 * Recursively searches the whole tree so will print
 * all the matching file.
 * Arguments
 *   pRoot        - root of current subtree
 *   targetName   - name we are looking for
 * Returns 1 if at least one instance of the file was found
 * or 0 if none found.
 */
int findFile(FILE_ENTRY_T *pRoot, char *targetName)
{
    int i = 0;
    int result = 0;
    if (strcmp(pRoot->filename, targetName) == 0)
    {
	char *path = getFullPath(pRoot);
	if (path != NULL)
	{
	    printf("Found: %s\n", path);
	    result = 1;
	}
	else
	{
	    printf("Memory allocation error creating full name\n");
	}
    }
    if (pRoot->bDirectory)
    {
	for (i = 0; i < pRoot->childCount; i++)
	    result |= findFile(pRoot->childFiles[i], targetName);
    }
    return result;
}

/* Search the tree to see if you can find a file/directory
 * If so, return a pointer to that FILE_ENTRY_T
 * Argument
 *    path    -  full filename including path
 * Returns pointer to FILE_ENTRY_T representing this file, or null.
 */


int main(int argc, char *argv[])
{
    char directory[PATH_MAX];
    char searchFile[PATH_MAX];
    char input[PATH_MAX];
    if (argc < 2)
    {
	printf("Argument error\n");
	printf("Usage:   directoryTree <directoryname>\n\n");
	exit(0);
    }
    strcpy(directory, argv[1]);
    if (buildTree(NULL, directory) == 0)
    {
	printf("Error building tree\n");
	exit(1);
    }
    else
    {
	printf("Contents of tree: \n");
	printTree(pRootDirectory);
    }
    cleanupList();
    while (1)
    {
	printf
	    ("Enter name of file to search for (without path, RETURN to exit): ");
	fgets(input, sizeof(input), stdin);
	memset(searchFile, 0, sizeof(searchFile));
	sscanf(input, "%s", searchFile);
	if (strlen(searchFile) == 0)
	    break;
	if (findFile(pRootDirectory, searchFile) == 0)
	    printf("*** %s not found in the tree\n", searchFile);
    }
    return 0;
}
