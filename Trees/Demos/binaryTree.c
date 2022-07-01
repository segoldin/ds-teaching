/*
 * binaryTree
 *
 *  This module implements a binary tree
 *
 *  The values associated with nodes in this tree are
 *  strings. This module could be made more general
 *  by making the data be void* and providing a 
 *  comparison function.
 *
 *  This binary tree is not balanced.
 *
 *  Created by Sally Goldin, 27 October 2011 for CPE113
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  

/* Structure representing a node in the tree */
typedef struct _node
{
  char* data;               /* pointer to the data represented by this node */ 
  int count;                /* handle duplicates. If count > 1, means there */
                            /* were multiple inserts of the same value */
  struct _node * left;      /* left child node in the tree */
  struct _node * right;     /* right child node in the tree */
} NODE_T;


/* Structure representing a tree */
typedef struct _tree
{
  NODE_T * root;            /* root of the tree */
  int itemcount;            /* number of items in the tree */
                            /* could be more than the number of nodes */
                            /*   because duplicate items use a single node */
} TREE_T;


/** Private functions ***/

/* compare the data in two nodes 
 * Arguments
 *     node_a         - first node
 *     node_b         - second node
 * Returns -1 if data in node_a is less than node_b (earlier in sort order)
 * Returns 1 if data in node_a is greater than node_b
 * Returns 0 if equal
 */  
int compare(NODE_T * node_a, NODE_T * node_b)
{
  return strcmp(node_a->data, node_b->data);
}


/* Recursive function to insert a new node in its
 * correct location in the tree 
 * Arguments
 *    pTree       - pointer to a tree or subtree
 *    pNewNode    - new node - data already assigned
 */
void insertNode(NODE_T* pRoot, NODE_T* pNewNode)
{
    /* case 1 - data is the same */
  if (compare(pNewNode,pRoot) == 0)
     {
     pRoot->count++;  /* just increment the counter */
     free(pNewNode->data);/* get rid of the extra copy of the data */
     free(pNewNode);  /* and get rid of the extra node */
     }
  /* case 2 - data in new node is smaller, should be in left subtree */ 
  else if (compare(pNewNode,pRoot) < 0)
     {
     if (pRoot->left == NULL)
         {
	 pRoot->left = pNewNode;
         }
     else  /* no room at this node, push further down the left branch */
         {
	 insertNode(pRoot->left,pNewNode);
         }
     }
  /* case 3 - data in new node is bigger, put in right subtree */ 
  else
     {
     if (pRoot->right == NULL)
         {
	 pRoot->right = pNewNode;
         }
     else  /* no room at this node, push further down the left branch */
         {
	 insertNode(pRoot->right,pNewNode);
         }
     }
}

/* Traverse a tree (in order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traverseInOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
    if (pCurrent->left != NULL)
       {
       traverseInOrder(pCurrent->left,nodeFunction); 
       }
    (*nodeFunction)(pCurrent);
    if (pCurrent->right != NULL)
       {
       traverseInOrder(pCurrent->right,nodeFunction); 
       }
}


/* Traverse a tree (post order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traversePostOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
    if (pCurrent->left != NULL)
       {
       traversePostOrder(pCurrent->left,nodeFunction); 
       }
    if (pCurrent->right != NULL)
       {
	 traversePostOrder(pCurrent->right,nodeFunction); 
       }
    (*nodeFunction)(pCurrent);
}


void printNode(NODE_T* pNode)
{
    int i = 0;
    /* handle the problem of multiple copies */
    for (i = 0; i < pNode->count; i++)
       printf("%s\n",pNode->data);
}

void freeNode(NODE_T* pNode)
{
  free(pNode->data);  /* we allocated this, so we delete it */
  free(pNode);
}


/* Traverse a tree (in order traversal) and
 * store items in sorted order in the passed array.
 * Argument
 *    pCurrent     -   current node
 *    array        -   array of char * pointers to be filled
 *    pIndex       -   pointer to index of current spot in the array
 * Return 1 unless there is a memory allocation error,
 * then return 0.
 */
int storeSortedData(NODE_T* pCurrent,char* array[], int * pIndex )
{
    int i = 0;
    int status = 1;
    if (pCurrent->left != NULL)
       {
       status = storeSortedData(pCurrent->left,array,pIndex); 
       }
    if (status)  /* no memory error  in left branch */
       {
       for (i=0; i < pCurrent->count; i++) 
          /* store multiple copies for dups */
          {
          char* dataCopy = strdup(pCurrent->data);
          if (dataCopy == NULL)
	     {
             status = 0;
             break;
             }  
          array[*pIndex] = dataCopy;
          *pIndex = *pIndex + 1;
          }
       }
    if (status)  /* no memory error at current node */
       {
       if (pCurrent->right != NULL)
          {
          status = storeSortedData(pCurrent->right,array,pIndex); 
          }
       }
    return status;
}



/** Public functions **/

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeHeap' when it no longer needs
 * the heap.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree()
{
    TREE_T * pTree = calloc(1,sizeof(TREE_T));
    return pTree;
}


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
int insertItem(TREE_T* pTree, char* pDataItem)
{
    int status = 1;
    char* pNewDataItem = NULL;
    NODE_T * pNewNode = NULL;
    /* create a copy of the data */
    pNewDataItem = strdup(pDataItem);
    /* create the new node */
    pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
    if ((pNewNode == NULL) || (pNewDataItem == NULL))
       {
       status = 0;
       }
    else
       {
       pNewNode->data = pNewDataItem;
       pNewNode->count = 1;
       if (pTree->root == NULL)
          {
          pTree->root = pNewNode;
          }
       else
	  {    
          insertNode(pTree->root,pNewNode);
          }
       pTree->itemcount++; 
       } 
    return status;
}

/* Traverse the tree (in order traversal) to store
 * the data values in the passed array.
 * Arguments
 *   pTree    -  Handle to tree
 *   array    -  Empty array of char *
 * Returns 1 unless there is a memory allocation error,
 * then 0
 */
int retrieveSortedData(TREE_T* pTree,char* array[])
{
   int index = 0;  /* to keep track of next slot */
   storeSortedData(pTree->root,array,&index);
}

/* Traverse and print give the ptr to the public
 * structure
 * Argument
 *   pTree   - public structure
 */
void printTree(TREE_T * pTree)
{
   traverseInOrder(pTree->root,&printNode);
} 



/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree)
{
   traversePostOrder(pTree->root,&freeNode);
} 

#ifdef DEBUG
/* this main is a test driver to see if the functions in this
 * module work correctly. It will not be compiled unless
 * -DDEBUG is specified on the compiler command line, e.g.
 * 
 *  gcc -DDEBUG -o binaryTree binaryTree.c
 *
 */
int main(int argc, char* argv[])
{

  char* samples[] = {"What a day","Fred","I love C","Alphabet",
                     "Zoology","Sunshine","Babysitter","Roast Duck",
		     "Japanese","Nothing to say","Mai Pen Rai",
                     "Who are you?","Yes","No","Maybe","123",
                     "Ant City","Captain Kirk","Japanese"};

  int sampleCount = sizeof(samples)/sizeof(char*);
  int i = 0;
  TREE_T * pMyTree = createTree();
  if (pMyTree == NULL)
    {
    printf("Memory allocation error creating new tree\n");
    exit(1);
    }
  printf("Successfully created the tree!\n");

  for (i = 0; i < sampleCount; i++)
    {
    if (!insertItem(pMyTree,samples[i]))
       {
       printf("Memory allocation error inserting new item\n");
       break;
       }
    }

  printf("Let's print them in order!\n\n");
  printTree(pMyTree);
  printf("\n\nOkay, free the tree\n");
  freeTree(pMyTree);

}
#endif
