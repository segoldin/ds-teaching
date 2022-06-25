/** CoupleDemo.java
 * 
 * Simple demonstration programming showing the use of structs/objects and relationships
 * between them.
 *
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 25 June 2022
 * Modified by: PUT YOUR NAME HERE
 */


import java.util.Scanner;

/** 
 * This class keeps a linked list of CoupleDemo instances, which can
 * point to each other in order to indicate partnering.
 * This version is incomplete, with tasks to be finished by the student.
 */ 

public class CoupleDemo
{


    /** object to use for getting terminal input */
    private static Scanner scan = new Scanner(System.in);

    /** keep track of number of people in the list */
    public static int peopleCount = 0;
    
    public static CoupleDemo headNode = null;            // first node in the list
    public static CoupleDemo tailNode = null;            // last node in the list

    /** Each person has a name */
    public String name;

    /** Each person has a gender */
    public String gender;
    
    /** Each person may have a partner, which is an instance of another CoupleDemo person */
    public CoupleDemo partner; 
    
    /** Each node in the list points to the next node */
    public CoupleDemo nextItem;

    /**
     * Constructor creates a new person (a CoupleDemo instance)
     * and sets its values
     */
    public CoupleDemo(String personName, String personGender)
    {
	name = personName;
	gender = personGender;
    }
    
    /** Given somone's name, try to find them in the list.
     * If found, return the instance, otherwise return null
     */
    public static CoupleDemo findPerson(String name)
    {
	CoupleDemo found = null;
	CoupleDemo current = headNode;
	while (current != null)
	{
	    if (current.name.equalsIgnoreCase(name))  // matched
	    {
		found = current;
		break;
	    }
	    current = current.nextItem;
	}
	return found;   // if name did not match any of the items, found will still be null
    }
    
    /** Make two people into a couple by setting their partner values
     * If the person already has a partner, print a message and 
     * set the old partner's 'partner' value to null.
     *     personA  -  name of first person
     *     personB  -  name of the second person
     */
    public static void makeCouple(String personA, String personB)
    {
	CoupleDemo a = findPerson(personA);
	if (a == null)
	{
	    System.out.print("No person found with name " + personA);
	    return;
	}
	CoupleDemo b = findPerson(personB);
	if (b == null)
	{
	    System.out.print("No person found with name " + personB);
	    return;
	}
	if (a == b)
	{
	    System.out.print("Person A and Person B are the same person!\n");
	    return;
	}
	if (a.partner != null)
	{
	    System.out.println(a.name + " is currently partnered with " + a.partner.name + " - breaking them up");
	    a.partner.partner = null;
	    // if we don't do this, the old partner will still be recorded
	    // as being in a couple
	}
	if (b.partner != null)
	{
	    System.out.println(b.name + " is currently partnered with " + b.partner.name + " - breaking them up");
	    b.partner.partner = null;
	    // if we don't do this, the old partner will still be recorded
	    // as being in a couple
	} 
	a.partner = b;
	b.partner = a;
	System.out.println(a.name + " and " + b.name + " are now a couple\n");
    }

    /** Create some initial values for the linked list
     */
    public static void initList()
    {
	CoupleDemo newPerson = new CoupleDemo("FRANK","M");
	headNode = tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("JENNY","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("SOMCHAI","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("ANCHALEE","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("MARK","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("JIM","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("MARY","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("ROBERT","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("SUSAN","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("WICHIAN","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("BUNDIT","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("KATE","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("LENNY","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("ARIYA","F");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	newPerson = new CoupleDemo("SAM","M");
	tailNode.nextItem = newPerson;
	tailNode = newPerson; peopleCount++;
	System.out.println("There are currently " + peopleCount + " people in the list");
    }


    /* Ask the user a question and get a string as a reply
     * @param  prompt --  Question or message
     * @return  answer from the user
     */
    public static String promptForString(String question)
    {
	System.out.print(question +" ");
	String input = scan.nextLine();
	return input;
    }


    /* Main function
     * Provides a menu - only some of the items are implemented
     */
    public static void main(String args[])
    {
      int option = 0;  // item chosen from menu
      String input;  // get input from the user
      String name1;
      String name2;
      String gender;
    
      System.out.println("Welcome to Couples!");
      initList();
      while (option != 10)
      {
	  System.out.print("\n  1 -  Make a couple\n");
	  System.out.print("  2 -  Print all couples\n");
	  System.out.print("  3 -  Break up a couple\n");
	  System.out.print("  4 -  Print all people's names\n");
	  System.out.print("  5 -  Add new person\n");
	  System.out.print("  10 - Exit\n");	
	  input = promptForString("Enter option number:");
	  try 
	  {
	      option = Integer.parseInt(input);
	  }
	  catch (NumberFormatException nfe)
	  {
	      System.out.println("Invalid integer!");
	      continue;
	  }
	  if (option == 1)
	  {
	      name1 = promptForString("\nFirst person's name?");
	      name2 = promptForString("Second person's name?");
	      makeCouple(name1,name2);
	  }
	  else if (option == 2)
	  {
	      System.out.print("\nHere is the current list of couples:\n");
	      CoupleDemo current = headNode;
	      while (current != null)
	      {
		  if (current.partner != null)
		      System.out.println(current.name + " is partnered with " + current.partner.name);
		  current = current.nextItem;
	      }
	      System.out.println("[END OF LIST]\n");
	      // Note this will print each couple twice - BONUS ASSIGNMENT... FIX THIS!
	  }
	  else if (option == 3)
	  {
	      name1 = promptForString("\nFirst person's name?");
	      name2 = promptForString("Second person's name?");
	      System.out.print("Not yet implemented!\n");
	      // ASSIGNMENT ONE - Write the code here to make person A and person B NOT be 
	      // a couple anymore. If they aren't a couple now, print a message
	      // tell the user this.
	      // If either name does not exist, print a message to tell the user this.
	  }
	  else if (option == 4)
	  {
	      System.out.print("\nHere is the current list of names:\n");
	      CoupleDemo current = headNode;
	      while (current != null)
	      {
		  System.out.println(current.name);
		  current = current.nextItem;
	      }
	      System.out.print("[END OF LIST]\n");
	  }
	  else if (option == 5)
	  {
	      name1 = promptForString("\nNew person's name?");
	      gender = promptForString("New person's gender?");
	      System.out.print("Not yet implemented!\n");	    
	      // ASSIGNMENT TWO: Write the code here to add a new person
	      // to the people array.
	      // DON'T FORGET TO: add 1 to peopleCount 
	      // To be completely correct, you also need to check that there
	      // is not already a person with this name in the list.
	  }	
	  else if (option != 10)
	  {
	      System.out.print("INVALID OPTION NUMBER!\n");
	  }
	}
      }
}
