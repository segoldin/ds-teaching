/*  universityTree.c
 *
 *  Partially complete program giving students the chance to work with trees
 *  Created by Sally Goldin, 1 July 2022 for AiCE Warp Data Structures competency
 *  Modified by YOUR NAME HERE
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAX_CHILDREN 20

#define UNIVERSITY 0
#define SCHOOL 1
#define DEPARTMENT 2
#define PROGRAM 3

/* for printing the node type */
char * nodeTypeTitles[] = {"University","School","Department","Program"};

/* Structure to represent one node in the tree.
 * A node is a university, school, department or program
 */
typedef struct _node
{
    char title[256];       /* title of this node */
    int type;              /* what kind of node? This will determine what its parent can be */
    struct _node* children[MAX_CHILDREN];   /* Array of pointers to children */
    int childCount;    	   /* How many children so far? */
    struct _node* parent;  /* convenient link to parent node */
} NODE_T;

/* Find a node based on its title. 
 * This code uses a recursive algorithm (preOrder traversal) which we'll study next week.
 * Returns a pointer to the matching node, or a NULL pointer if not found
 */
NODE_T * findNode(NODE_T* current, char searchTitle[])
{
    NODE_T * found = NULL;
    if (strcasecmp(current->title,searchTitle) == 0)
      found = current;
    else
    {
      int i;
      for (i = 0; i < current->childCount; i++)
      {
	found = findNode(current->children[i],searchTitle);
	if (found != NULL)   /* got it! */
	  break;
      }
    }
    return found;
}

/* Add a node as the child of another node.
 * If the parent node's list of children is full, return 0 for error.
 * If the parent node is the wrong type (should be one less than current type), return 0
 * Otherwise return 1 for success
 */
int insertChildNode(NODE_T * parent, NODE_T * child)
{
  int result = 1;
  if (parent->type != (child->type - 1))
  {
    printf("Parent is the wrong type for child!\n");
    result = 0;
  }
  else if (parent->childCount == MAX_CHILDREN)
  {
    printf("Parent has no room for more children\n");
    result = 0;
  }
  else
  {
    parent->children[parent->childCount] = child;
    parent->childCount++;
    child->parent = parent;
  }
  return result;
}

/* Print a tree node and its children.
 * This code uses a recursive algorithm (preOrder traversal) which we'll study next week.
 */
void printNode(NODE_T* current)
{
  int i;
  for (i = 0; i < current->type; i++) printf("----");
  printf(" %s (%s)\n",current->title,nodeTypeTitles[current->type]);
  if (current->childCount > 0)
  {
    for (i = 0; i < current->childCount; i++)
    {
      printNode(current->children[i]);
    }
  }
}

/* Add a few nodes to the tree
 * so we have something to print.
 */
void initTree(NODE_T * root)
{
  NODE_T * node = NULL;		// used for creating other nodes
  NODE_T * parentNode = NULL;   // used in initialization
  /* add a few schools 
   * Find the full list here: https://www.kmitl.ac.th/current-students - Academic Divisions 
   */
  node = calloc(1,sizeof(NODE_T));   
  if (node == NULL)
  {
    printf("Error allocating node - exiting!\n");
    exit(1);
  }
  strcpy(node->title,"School of Engineering");
  node->type = SCHOOL;
  insertChildNode(root,node);
  
  node = calloc(1,sizeof(NODE_T));    
  if (node == NULL)
  {
    printf("Error allocating node - exiting!\n");
    exit(1);
  }
  strcpy(node->title,"School of Science");
  node->type = SCHOOL;
  insertChildNode(root,node);
  
  /* add a few departments */
  parentNode = findNode(root,"School of Engineering");
  if (parentNode != NULL)
  {
    node = calloc(1,sizeof(NODE_T));   
    if (node == NULL)
    {
      printf("Error allocating node - exiting!\n");
      exit(1);
    }
    strcpy(node->title,"Mechanical Engineering");
    node->type = DEPARTMENT;
    insertChildNode(parentNode,node);
    
    node = calloc(1,sizeof(NODE_T));   
    if (node == NULL)
    {
      printf("Error allocating node - exiting!\n");
      exit(1);
    }
    strcpy(node->title,"Computer Engineering");
    node->type = DEPARTMENT;
    insertChildNode(parentNode,node);
  }
  
  parentNode = findNode(root,"School of Science");
  if (parentNode != NULL)
  {
    node = calloc(1,sizeof(NODE_T));   
    if (node == NULL)
    {
      printf("Error allocating node - exiting!\n");
      exit(1);
    }
    strcpy(node->title,"Chemistry");
    node->type = DEPARTMENT;
    insertChildNode(parentNode,node);
    
    node = calloc(1,sizeof(NODE_T));   
    if (node == NULL)
    {
      printf("Error allocating node - exiting!\n");
      exit(1);
    }
    strcpy(node->title,"Physics");
    node->type = DEPARTMENT;
    insertChildNode(parentNode,node);
  }
  
  /* add a program */
  parentNode = findNode(root,"Computer Engineering");
  if (parentNode != NULL)
  {
    node = calloc(1,sizeof(NODE_T));   
    if (node == NULL)
    {
      printf("Error allocating node - exiting!\n");
      exit(1);
    }
    strcpy(node->title,"CIE Program");
    node->type = PROGRAM;
    insertChildNode(parentNode,node);
  }
}

/* Get the information, then add a new node into the tree
 * Need to know the details of the node, plus what its parent 
 * should be.
 */
void addNewNode(NODE_T* root)
{
  char input[256];
  char title[256];
  char parentTitle[256];
  int type;
  printf("Title for new node? ");
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%s",title);
  printf("Type for new node? (1=school, 2=department, 3=program) ");
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%d",&type);
  if ((type < 1) || (type > 3))
  {
    printf("Invalid node type!\n");
    return;
  }
  printf("Title of parent node? ");
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%s",parentTitle);
  printf("NOT YET IMPLEMEMENTED\n");
  // ADD CODE HERE TO:
  //   -- look up the parent node
  //   -- if successful, create the child node
  //   -- set the title and type of the child node
  //   -- add the child to the parent
  // Don't forget to check the results of each step
  // For instance, if the parent doesn't exist, you should
  // give an error message and return.
}


/* Get the information about the node to remove
 * Search the tree to find it, then remove it. 
 * CAREFUL - if the node has children, you need to remove those
 * first!
 */
void removeNode(NODE_T* root)
{
  char input[256];
  char title[256];
  char parentTitle[256];
  int type;
  printf("Title for node to remove? ");
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%s",title);
  printf("NOT YET IMPLEMEMENTED\n");
  // ADD CODE HERE TO:
  //   -- Look up the node to be removed
  //   -- If found, see if it is a leaf (childCount == 0)
  //      If not, print an error telling the user they must
  //      delete the children first and return
  //   -- Otherwise, use the parent link to find the parent
  //   -- Remove the node from the parent array -- you might have to move the other
  //      children earlier in the array to fill the "hole"
  //   -- Delete 1 from the parent's childCount
  //   -- Free the memory for the removed node 
  //         free(removedNode);
}

/* Main function creates the root node and adds
 * some nodes into the tree, then displays a menu with
 * functions, some of which the student is required to implement.
 */
int main(int argc, char* argv[])
{
  NODE_T * root = NULL;		// root node of our tree
  char input[256];        	// for getting data from the user
  int option = 0;		// menu option

  /* start by adding some items to the tree */
  root = calloc(1,sizeof(NODE_T));   // create the root 
  if (root == NULL)
  {
    printf("Error allocating root node - exiting!\n");
    exit(1);
  }
  strcpy(root->title,"KMITL");
  root->type = UNIVERSITY;
  initTree(root);
  
  printf("Here is the starting tree for KMITL:\n");
  printNode(root);
  while (option != 10)
  {
    printf("\nAvailable options:\n");
    printf("\t1 Print current tree\n");
    printf("\t2 Add new tree node\n");
    printf("\t3 Remove tree node\n");
    printf("\t10 Exit the program\n");
    printf("Enter option: ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&option);
    switch (option)
    {
      case 1:
	printNode(root);
	break;
      case 2:
	addNewNode(root);  // see partially implemented function above main
	break;
      case 3:
	removeNode(root);  // see partially implemented function above main
	break;
      case 10:
	printf("Goodbye!\n");
	exit(0);
      default:
	printf("Illegal option. Please try again!\n");
    }
  }
}
