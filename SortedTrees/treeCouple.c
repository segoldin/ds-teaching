/* treeCouple.c
 * 
 * Expand the "couples" program to store people in a sorted binary tree.
 * This allows unlimited number of people as well as speeding up search.
 *
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 10 July 2022
 * This version has missing code for the student to implement
 * MODIFIED BY [YOUR NAME HERE]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _person 
{
    char name[32];         			// first name
    char gender[2];        			// either "M" or "F"
    int age;		   				// age in years
    int printed;                    // tells us whether this node has been printed or not
    struct _person * partner;  		// pointer to this person's partner
                           			// if NULL, no partner
    struct _person * leftChild;  	// pointer to the left child of this node
    struct _person * rightChild; 	// pointer to the right child of this node
} PERSON_T;

PERSON_T * root = NULL;             // for convenience, make the root a global variable
                                    // once it it set, it will not change
int peopleCount = 0;				// global count of number of people
    
   /** Given somone's name, try to find them in the tree
 	* Uses a recursive, pre-order traversal.
 	* If found, return the instance, otherwise return NULL
	* Assumes the tree is sorted by the smaller-left,larger-right rule
 	*/
	PERSON_T * findPerson(PERSON_T* current, char * name)
    {
		if (current == NULL)  // this way, we don't need to check if there are children
			return current;
		if (strcmp(name,current->name) == 0) // equal?
			return current;
		if (strcmp(name,current->name) < 0)  // new name is earlier in alphabet
	    	return findPerson(current->leftChild,name);
		else
	    	return findPerson(current->rightChild,name);
	}
    
    /** 
     * Make two people into a couple by setting their partner values
     * If the person already has a partner, print a message and 
     * set the old partner's 'partner' value to NULL.
     *     personA  -  name of first person
     *     personB  -  name of the second person
     */
    void makeCouple(char * personA, char * personB)
    {
		PERSON_T * a = findPerson(root,personA);
		if (a == NULL)
		{
	    	printf("No person found with name %s\n",personA);
	    	return;
		}
		PERSON_T * b = findPerson(root,personB);
		if (b == NULL)
		{
	    	printf("No person found with name %s\n",personB);
	    	return;
		}
		if (a == b)
		{
	    	printf("Person A and Person B are the same person!\n");
	    	return;
		}
		if ((a->age < 13) || (b->age < 13))
		{
		    printf("At least one person is too young to be in a couple!\n");
			return;
		}
		if ((a->partner != NULL) && (a->partner != b))
		{
		    printf("%s is currently partnered with %s - breaking them up\n",a->name,a->partner->name);
	    	a->partner->partner = NULL;
	    	// if we don't do this, the old partner will still be recorded
	    	// as being in a couple
		}
		if ((b->partner != NULL) && (b->partner != a))
		{
			printf("%s is currently partnered with %s - breaking them up\n",b->name,b->partner->name);
	    	b->partner->partner = NULL;
		} 
		a->partner = b;
		b->partner = a;
		printf("%s and %s are now a couple\n",a->name,b->name);
    }

    /** If two people are a couple, separate them. 
     *     personA  -  name of first person
     *     personB  -  name of the second person
     */
	void breakCouple(char * personA, char * personB)
    {
		PERSON_T * a = findPerson(root,personA);
		if (a == NULL)
		{
	    	printf("No person found with name %s\n",personA);
	    	return;
		}
		PERSON_T * b = findPerson(root,personB);
		if (b == NULL)
		{
	    	printf("No person found with name %s\n",personB);
	    	return;
		}
		if (a == b)
		{
	    	printf("Person A and Person B are the same person!\n");
	    	return;
		}
		if (a->partner != b)
		{
	    	printf("%s is not a couple with %s\n",personA,personB);
	    	return;
		}
		// otherwise we can break them up by setting their partner fields to NULL
		a->partner = NULL;
		b->partner = NULL;
		printf("%s and %s have broken up!\n",a->name,b->name);
	}
    

    /**
     * Use the sorted binary tree rule to figure out where to insert a new node.
     * Assumes that the fields of the new Node have already been set.
     * Also assumes that we've checked for a duplicate name. 
     * Uses a recursive algorithm to find the right place in the tree.
     * @param  	current		Potential parent node we are checking
     * @param 	newNode		New node we are trying to insert.
     */
    void insertNode(PERSON_T * current, PERSON_T * newNode)
    {
    	if (strcasecmp(newNode->name,current->name) < 0)  // new name is earlier in alphabet
    	{
	    	if (current->leftChild == NULL)
	    		current->leftChild = newNode;  // if there's room, put it as left child
	    	else 
	    		insertNode(current->leftChild,newNode); // otherwise, go to the left to find the correct spot
    	}
		else
		{
	    	if (current->rightChild == NULL)
	    		current->rightChild = newNode;  // if there's room, put it as right child
	    	else 
	    		insertNode(current->rightChild,newNode); // otherwise, go to the right to find the correct spot	    	
		}
    }

    /* "CONSTRUCTOR" function for a person
     * Allocate a new person and set the field values
     * Returns the pointer to the person.
     * If allocation fails, exits the program
     */
    PERSON_T * createPerson(char* name, char * gender, int age)
    {
    	PERSON_T * newperson = calloc(1,sizeof(PERSON_T));
    	if (newperson == NULL)
    	{
    		printf("Memory allocation error creating new person! Exiting!");
    		exit(1);
    	}
    	strcpy(newperson->name,name);
    	strcpy(newperson->gender,gender);
    	newperson->age = age;
    	return newperson;
    }
    
    /**
     * Print the details of the current node
     */
    void printInfo(PERSON_T * person)
    {
    	printf("%s\t (%s, age %d)\n",person->name,person->gender,person->age);
    }

    /** Create some initial values for the tree
     */
    void initTree()
    {
		PERSON_T * newPerson = createPerson("FRANK","M",25);
		root = newPerson; 
		peopleCount++;
		newPerson = createPerson("JENNY","F",32);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("SOMCHAI","M",19);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("ANNA","F",37);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("MARK","M",25);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("JIM","M",20);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("MARY","F",12);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("ROBERT","M",87);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("SUSAN","F",43);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("WICHIAN","M",17);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("BUNDIT","M",52);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("KATE","F",22);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("LENNY","M",10);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("ARIYA","F",13);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = createPerson("SAM","M",22);
		insertNode(root,newPerson);
		peopleCount++;
		printf("There are currently %d people in the list\n",peopleCount);
    }

    /**
     * Print the people in the tree in ascending sorted order
     * This is a recursive function that does an in-order traversal.
     * @param	current		Tree node where we are currently located
     */
    void printPeople(PERSON_T * current)
    {
    	if (current->leftChild != NULL)
    		printPeople(current->leftChild);
    	printInfo(current);
    	if (current->rightChild != NULL)
    		printPeople(current->rightChild);
    }

   /**
     * Print the people in the tree in descending sorted order
     * @param	current		Tree node where we are currently located
     */
    void printPeopleDescending(PERSON_T * current)
    {
    	printf("LEFT FOR THE STUDENT TO IMPLEMENT!\n");
    }


    /** 
     * Print all the current couples.
     * Uses an in-order traversal (recursive) so the first name of the coupld
     * will be alphabetical. 
     * Uses the printed flag to avoid printing the same couple twice.
     */
    void printCouple(PERSON_T * current)
    {
    	if (current == NULL)  // removes the need to check before recursive calle
    		return;
    	// go down the left branch
    	printCouple(current->leftChild);
    	// deal with this node
    	if (current->partner != NULL)
    	{
    		if (current->printed == 0)
			{
				printf("%s is partnered with %s\n",current->name,current->partner->name);
				current->partner->printed = 1;  // so we won't print twice
			}
			else // don't print, but reset the printed flag is necessary
			{
				current->printed = 0;
			}
    	}
    	// go down the right branch
    	printCouple(current->rightChild);
    }


    /* Ask the user a question and get a string as a reply
	 *   prompt --  Question or message
 	 *   answer --  String (array) to use for the answer
 	*/
	void promptForString(char* question, char* answer)
	{
    	char buffer[265];
    	printf("%s ",question);
    	fgets(buffer,sizeof(buffer),stdin);
    	sscanf(buffer,"%s",answer);  // note will get only the first word
	}

	/* Change the passed string to upper case 
	 */
	void upperCase(char string[])
	{
    	int i;
    	for (i = 0; i < strlen(string); i++)
		string[i] = toupper(string[i]);
	}

    /* Main function
     * Provides a menu - only some of the items are implemented
     */
    int main(int argc,char * argv[])
    {
    	int option = 0;  // item chosen from menu
      	char input[256];  // get input from the user
      	char name1[256];
      	char name2[256];
      	char gender[16];
      	int age;
    
      	printf("Welcome to Couples!");
      	initTree();
      	while (option != 10)
      	{
	  		printf("\n  1 -  Make a couple\n");
	  		printf("  2 -  Print all couples\n");
	  		printf("  3 -  Break up a couple\n");
	  		printf("  4 -  Print all people's names (ascending sort)\n");
	  		printf("  5 -  Print all people's names (descending sort)\n");
	  		printf("  6 -  Add a new person\n");
	  		printf(" 10 -  Exit\n");	
			promptForString("Enter option number:",input);
			sscanf(input,"%d",&option); // change to integer
	  		if (option == 1)
	  		{
	  			promptForString("\nFirst person's name?",name1);
	      		promptForString("Second person's name?",name2);
	      		upperCase(name1);
	      		upperCase(name2);
	      		makeCouple(name1,name2);
	      	}
	  		else if (option == 2)
	  		{
	  			printf("\nHere is the current list of couples:\n");
	  			printCouple(root);
	  		}
	  		else if (option == 3)
	  		{
	  			promptForString("\nFirst person's name?",name1);
	  			promptForString("Second person's name?",name2);
	  			upperCase(name1);
	  			upperCase(name2);
	  			breakCouple(name1,name2);
	  		}
	  		else if (option == 4)
	  		{
	  			printf("\nHere is the current list of names (ascending sort):\n");
	  			printPeople(root);
	  			printf("[END OF LIST]\n");
	  		}
	  		else if (option == 5)
	  		{
	  			printf("\nHere is the current list of names (descending sort):\n");
	  			printPeopleDescending(root);
	  			printf("[END OF LIST]\n");	  			
	  		}
	  		else if (option == 6)
	  		{
	  			promptForString("\nNew person's name?",name1);
	  			promptForString("New person's gender?",gender);
	  			upperCase(name1);
	  			upperCase(gender);
	  			promptForString("New person's age?",input);
	  			sscanf(input,"%d",&age);
	  			printf("LEFT FOR THE STUDENT TO IMPLEMENT!\n");
	      	}
	  		else if (option != 10)
	  		{
	  			printf("INVALID OPTION NUMBER!\n");
	  		}
	  	}
	}
