/* arrayListDemo.c
 * 
 * Simple program showing how an array can be used to implement a list data structure.
 * This version uses only integers as list elements.
 * 
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 14 June 2022
 * Modified by: PUT YOUR NAME HERE
 */

#include <stdio.h>
#define MAXVALS 10

/* Main function declares an array, then asks the user for values until
 * the user either enters a negative number, or the array is full.
 */
int main(int argc, char* argv[])
{
    int exampleList[MAXVALS];      // we can hold up to ten values in our list
    int count = 0;                 // how many values do we have so far?
    int i = 0;                     // use this as an index to the array/list elements
    int position;                  // use for Part 4, inserting in the middle
    char input[64];                // for getting what the user types
    int value = 0;                 // turn what the user types into a number
    
    // Part 1 - get the values
    while ((value >= 0) && (count < MAXVALS)) // we will stop when the user enters a negative 
                                              // or when the list is full 
    {
	printf("Enter a positive, whole number (negative to stop): ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&value);
	if ((value >= 0) && (count < MAXVALS))
	{  
	  exampleList[i] = value;
	  i = i + 1;
	  count = count+1;
	  printf(" --- List now holds %d items\n",count);
	}
    }
  
    // Part 2 - print the values in order
    printf("\nHere is the current contents of the list, from first to last item: \n");
    i = 0;                         // start at the beginning
    /** Remove the comment characters before adding your code 
    while (i < count)
    {
         // WRITE YOUR CODE HERE to print list element 'i' 
         // then move on to the next list element
    }
      Remove before adding your code **/
    
    // Part 3 - print the values in reverse order
    printf("\nHere is the list contents, from last to first item: \n");
    i = count - 1;                         // start at the end
    /** Remove the comment characters before adding your code 
    while (i >= 0)
    {
         // WRITE YOUR CODE HERE to print list element 'i'
         // then move to the previous list element
    }
       Remove before adding your code **/
    
    // Part 4 - Advanced
    printf("\nLet's insert an item in the middle of the list: \n");
    printf("Insert what value (positive integer): ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&value);
    printf("Insert %d at what position (0 to %d): ",value,count);
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&position);
    // WRITE THE CODE HERE TO MOVE THE LIST ELEMENTS AND MAKE ROOM FOR INSERTION
    // See the lecture for a graphical example
    // Hint: there are some special cases you need to worry about
    //    1) the list is already full (can't insert)
    //    2) the selected position is at the end of the list (no need to move elements)
    
}