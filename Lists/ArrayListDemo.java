/** 
 * ArrayListDemo.java
 * 
 * Simple program showing how an array can be used to implement a list data structure.
 * This version uses only integers as list elements.
 * 
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 14 June 2022
 * Modified by: PUT YOUR NAME HERE
 */

import java.util.Scanner;

public class ArrayListDemo
{

  /** maximum number of list items */
  private static final int MAXVALS = 10;
  
  /** object to use for getting terminal input */
  private static Scanner scan = new Scanner(System.in);
  
/* Main function declares an array, then asks the user for values until
 * the user either enters a negative number, or the array is full.
 */
public static void main(String args[])
{
    int exampleList[] = new int[MAXVALS];      // we can hold up to ten values in our list
    int count = 0;                 	       // how many values do we have so far?
    int i = 0;                                 // use this as an index to the array/list elements
    int position;                              // use for Part 4, inserting in the middle
    String input;                              // for getting what the user types
    int value = 0;                             // turn what the user types into a number
    
    // Part 1 - get the values
    while ((value >= 0) && (count < MAXVALS)) // we will stop when the user enters a negative 
                                              // or when the list is full 
    {
	System.out.print("Enter a positive, whole number (negative to stop): ");
	input = scan.nextLine();
	value = Integer.parseInt(input);  // change to an int 
	if ((value >=0 ) && (count < MAXVALS))
	{
	  exampleList[i] = value;
	  i = i + 1;
	  count = count+1;
	  System.out.println(" --- List now holds " + count + " items\n");
	}
    }
  
    // Part 2 - print the values in order
    System.out.println("\nHere is the current contents of the list, from first to last item: \n");
    i = 0;                         // start at the beginning
    /** Remove the comment characters before adding your code 
    while (i < count)
    {
         // WRITE YOUR CODE HERE to print list element 'i' 
         // then move on to the next list element
    }
      Remove before adding your code **/
    
    // Part 3 - print the values in reverse order
    System.out.println("\nHere is the list contents, from last to first item: \n");
    i = count - 1;                         // start at the end
    /** Remove the comment characters before adding your code 
    while (i >= 0)
    {
         // WRITE YOUR CODE HERE to print list element 'i'
         // then move to the previous list element
    }
       Remove before adding your code **/
    
    // Part 4 - Advanced
    System.out.println("\nLet's insert an item in the middle of the list: \n");
    System.out.print("Insert what value (positive integer): ");
    input = scan.nextLine();
    value = Integer.parseInt(input);
    System.out.print("Insert " + value + " at what position (0 to " + count + "): ");
    input = scan.nextLine();
    position = Integer.parseInt(input);
    // WRITE THE CODE HERE TO MOVE THE LIST ELEMENTS AND MAKE ROOM FOR INSERTION
    // See the lecture for a graphical example
    // Hint: there are some special cases you need to worry about
    //    1) the list is already full (can't insert)
    //    2) the selected position is at the end of the list (no need to move elements)
    
}
}