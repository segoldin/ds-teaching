/*  
 *  filesearch.h
 *
 *  Header file for functions to get all the files in a directory
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */


/* Given a pathname plus filename string,
 * returns the part after the last separator.
 * which is assumed to be the node plus extension.
 * Tests for the Unix/Linux separator only.
 * @param pczInputFile filename with path
 * @return filename without path (actually, a pointer into the
 *         input buffer).
 */
char* stripPath(char* pczInputFile);

/*  Finds and returns a list of the names of files in a directory.
 *  Arguments
 *      directory      Full path name of the directory - no terminating /
 *      pCount         Pointer to integer for returning number of files found
 *                     Returns -1 if an error occurred.
 *  Returns dynamically allocated array of dynamically allocated
 *  strings with full file names including the path. This array
 *  will be freed at the start of the next call
 *  to getFileList so the caller should not do anything other than
 *  read this storage. If no files found or an error occurred, returns
 *  NULL. Check value stored in pCount to determine which.
 */
char ** getFileList(const char * directory, 
		    int* pCount);

/* Check to see if a filename is a directory.
 * Arguments
 *    filename           Name of file with full path
 * Returns 1 if this file is a directory, 0 if not.
 */
int isDirectory(const char* filename);

/*  Free any memory associated with the global 
 *  file list, and set the pointer to null.
 */
void cleanupList();
