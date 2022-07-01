/* coupleDemo.c
 * 
 * Simple demonstration program showing the use of structs/objects and relationships
 * between them.
 *
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 25 June 2022
 * Modified by: PUT YOUR NAME HERE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[32];         // first name
    char gender[2];           // either "M" or "F"
    int partner;           // index of this person's partner in the people[] array
                           // if zero, no partner
} PERSON_T;

// Initialize with some values. Leave the 0th element empty
PERSON_T people[30] =   
    {
      {"","",0},
      {"FRANK","M",0},{"JENNY","F",0},{"SOMCHAI","M",0},{"ANCHALEE","F",0},{"MARK","M",0},
      {"JIM","M",0},{"MARY","F",0},{"ROBERT","M",0},{"SUSAN","F",0},{"WICHIAN","M",0},      
      {"BUNDIT","M",0},{"KATE","F",0},{"LENNY","M",0},{"ARIYA","F",0},{"SAM","M",0}
    };  
    
int peopleCount = 15;

/* Given somone's name, try to find them in the people array.
 * If found, return the index in the array. Otherwise return 0.
 */
int findPerson(char* name)
{
    int i = 1;        // in this array, 0 element is unused.
    int found = 0;
    while (i <= peopleCount)
    {
        if (strcasecmp(people[i].name,name) == 0)  // matched
        {
            found = i;
            break;
        }
        i = i + 1;
    }
    return found;   // if name did not match any of the items, found will still be 0
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

/* Make two people into a couple by setting their partner values
 * If the person already has a partner, print a message and 
 * set the old partner's 'partner' value to 0.
 *     personA  -  name of first person
 *     personB  -  name of the second person
 */
void makeCouple(char* personA, char* personB)
{
    int a = findPerson(personA);
    if (a == 0)
    {
        printf("No person found with name '%s'\n",personA);
        return;
    }
    int b = findPerson(personB);
    if (b == 0)
    {
	printf("No person found with name '%s'\n",personB);
	return;
    }
    if (a == b)
    {
	printf("Person A and Person B are the same person!\n");
	return;
    }
    if (people[a].partner != 0)
    {
	printf("%s is currently partnered with %s - breaking them up\n",
	       people[a].name,people[people[a].partner].name);
	people[people[a].partner].partner = 0;
	// if we don't do this, the old partner will still be recorded
	// as being in a couple
    }
    if (people[b].partner != 0)
    {
      	printf("%s is currently partnered with %s - breaking them up\n",
	       people[b].name,people[people[b].partner].name);
        people[people[b].partner].partner = 0;
    }
    people[a].partner = b;
    people[b].partner = a;
    printf("%s and %s are now a couple\n\n",people[a].name,people[b].name);
}

/* Main function
 * Provides a menu - only some of the items are implemented
 */
int main(int argc, char* argv[])
{
    int option = 0;  // item chosen from menu
    int i = 0;       // used for looping through the array
    char input[32];  // get input from the user
    char name1[32];
    char name2[32];
    char gender[32];
    
    printf("Welcome to Couples!\n");
    while (option != 10)
    {
        printf("\n  1 -  Make a couple\n");
        printf("  2 -  Print all couples\n");
        printf("  3 -  Break up a couple\n");
        printf("  4 -  Print all people's names\n");
        printf("  5 -  Add new person\n");
        printf("  10 - Exit\n");	
        promptForString("Enter option number:",input);
        sscanf(input,"%d",&option); // change to integer
        if (option == 1)
        {
            promptForString("\nFirst person's name?",name1);
            promptForString("Second person's name?",name2);
            makeCouple(name1,name2);
        }
        else if (option == 2)
        {
            i = 1;
            printf("\nHere is the current list of couples:\n");
            while (i <= peopleCount)
            {
                if ((people[i].partner != 0) && (people[i].partner > i))
                    printf("%s is partnered with %s\n",people[i].name,
                        people[people[i].partner].name);
                // the check to make sure the partner is later in the array
                // allows us to print each couple only once
                i = i + 1;    
            }
            printf("[END OF LIST]\n");
        }
        else if (option == 3)
        {
    	    promptForString("\nFirst person's name?",name1);
            promptForString("Second person's name?",name2);
            printf("Not yet implemented!\n");
            // ASSIGNMENT ONE - Write the code here to make person A and person B NOT be 
            // a couple anymore. If they aren't a couple now, print a message
            // tell the user this.
            // If either name does not exist, print a message to tell the user this.
        }
        else if (option == 4)
        {
            i = 1;
            printf("\nHere is the current list of names:\n");
            while (i <= peopleCount)
            {
                printf("%s\n",people[i].name);
                i = i + 1;    
            }
            printf("[END OF LIST]\n");
        }
        else if (option == 5)
        {
            promptForString("\nNew person's name?",name1);
            promptForString("New person's gender?",gender);
            printf("Not yet implemented!\n");	    
            // ASSIGNMENT TWO: Write the code here to add a new person
            // to the people array.
            // DON'T FORGET TO: 1) add 1 to peopleCount 
            //                  2) make sure the array is not full
            //                      (peopleCount < 30)
            // To be completely correct, you also need to check that there
            // is not already a person with this name in the array.
        }	
        else if (option != 10)
        {
            printf("INVALID OPTION NUMBER!\n");
        }
    }
}
