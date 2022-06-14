/** 
 * LinkedListDemo.java
 * 
 * Simple program demonstrating a linked list.
 * This version uses only integers as list elements.
 * 
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 14 June 2022
 * Modified by: PUT YOUR NAME HERE
 */

import java.util.Scanner;

public class LinkedListDemo
{

  /** Each node in the list has a value */
  public int nodeValue;
  
  /** Each node in the list points to the next node */
  public LinkedListDemo nextItem;
  
  /** object to use for getting terminal input */
  private static Scanner scan = new Scanner(System.in);
  
  /* Main function declares an array, then asks the user for values until
   * the user either enters a negative number, or the array is full.
   */
  public static void main(String args[])
  {
    int count = 0;                 	       // how many values do we have so far?
    int position;                              // use for Part 4, inserting in the middle
    String input;                              // for getting what the user types
    int value = 0;                             // turn what the user types into a number
    LinkedListDemo headNode = null;            // first node in the list
    LinkedListDemo tailNode = null;            // last node in the list
    
    // Part 1 - get the values
    while (value >= 0)                        // we will stop when the user enters a negative 
                                              // Note that there is no limit on the number of items!
    {
	System.out.print("Enter a positive, whole number (negative to stop): ");
	input = scan.nextLine();
	value = Integer.parseInt(input);  // change to an int 
	LinkedListDemo node = new LinkedListDemo();
	node.nodeValue = value;
	if (value >= 0)
	{
	  count = count+1;
	  // link it into the list
	  if (headNode == null)                 // this is the first item in the list
	  {
	      headNode = tailNode = node;       // so it becomes both the first and last item
	  }
	  else  
	  {
	      tailNode.nextItem = node;         // set the tail to hold the new node
	      tailNode = node;                  // and now that new node is the tail
	  }
	  System.out.println(" --- List now holds " + count + " items\n");
	}
    }
  
    // Part 2 - print the values in order
    System.out.println("\nHere is the current contents of the list, from first to last item: \n");
    LinkedListDemo current = headNode;  
    /** Remove the comment characters before adding your code 
    while (current != null)
    {
         // WRITE YOUR CODE HERE to print current list element 
         // then move on to the next list element
    }
      Remove */
    
    // Part 3 - Advanced
    System.out.println("\nLet's insert an item in the middle of the list: \n");
    System.out.print("Insert what value (positive integer): ");
    input = scan.nextLine();
    value = Integer.parseInt(input);
    LinkedListDemo node = new LinkedListDemo(); // create the node to add
    node.nodeValue = value;
    System.out.print("Insert " + value + " at what position (0 to " + count + "): ");
    input = scan.nextLine();
    position = Integer.parseInt(input);
    // WRITE THE CODE HERE to insert the new node into the list at the right position
    // Hint: there are some special cases you need to worry about
    //    1) insert at the beginning (position 0)
    //    2) insert at the end of the list (position count)
    //    These cases are simpler than the general case where you need to go through the list
    //    to find the node that is currently at the position, and insert the new
    //    node before that existing node. 
    
  } // end of main
}