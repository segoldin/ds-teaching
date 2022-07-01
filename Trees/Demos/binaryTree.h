/*
 * binaryTree.h
 *
 * Functions and data structures for simple sorted binary
 * tree. 
 *
 * Created by Sally Goldin, 27 October 2011 for CPE113
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H

/* define a handle data type for the tree */
typedef struct _tree TREE_T;

/** Public functions **/

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeHeap' when it no longer needs
 * the heap.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree();


/* Insert a new node into the correct location in the tree.
 * The tree is subject to the constraint that for any node,
 * the data in its left child (if any) is less than its own
 * data and the data in its right child (if any) is greater
 * than its own.
 * Arguments
 *    pTree       - pointer
 *    pDataItem    - new data to be inserted in the tree 
 * Returns 1 for success, 0 if memory allocation error occurred.
 */
int insertItem(TREE_T * pTree, char* pDataItem);

/* Traverse the tree (in order traversal) to store
 * the data values in the passed array.
 * Arguments
 *   pTree    -  Handle to tree
 *   array    -  Empty array of char *
 * Returns 1 unless there is a memory allocation error,
 * then 0
 */
int retrieveSortedData(TREE_T* pTree,char* array[]);

/* Traverse and print give the ptr to the public
 * structure
 * Argument
 *   pTree   - public structure
 */
void printTree(TREE_T * pTree);


/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree);

#endif
