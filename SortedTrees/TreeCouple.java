/** TreeCouple.java
 * 
 * Expand the "couples" program to store people in a sorted binary tree.
 * This allows unlimited number of people as well as speeding up search.
 *
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 10 July 2022
 * This version has missing code for the student to implement
 * MODIFIED BY [YOUR NAME HERE]
 */


import java.util.Scanner;

/** 
 * This class keeps a sorted binary tree of PersonNode instances, which can
 * point to each other in order to indicate partnering.
 */ 
public class TreeCouple
{

    /** object to use for getting terminal input */
    private static Scanner scan = new Scanner(System.in);

    /** keep track of number of people in the list */
    public static int peopleCount = 0;
    
    /** Keep the root of the tree */
    public static PersonNode root = null;            

    
    /** Given somone's name, try to find them in the tree
     * Uses a recursive, pre-order traversal.
     * If found, return the instance, otherwise return null
     * Assumes the tree is sorted by the smaller-left,larger-right rule
     */
    public static PersonNode findPerson(PersonNode current, String name)
    {
		if (current == null)  // this way, we don't need to check if there are children
			return current;
		if (current.name.equalsIgnoreCase(name))
			return current;
		if (name.compareToIgnoreCase(current.name) < 0)  // new name is earlier in alphabet
	    	return findPerson(current.leftChild,name);
		else
	    	return findPerson(current.rightChild,name);
	}
    // see  https://www.w3schools.com/java/ref_string_comparetoignorecase.asp
    
    /** 
     * Make two people into a couple by setting their partner values
     * If the person already has a partner, print a message and 
     * set the old partner's 'partner' value to null.
     *     personA  -  name of first person
     *     personB  -  name of the second person
     */
    public static void makeCouple(String personA, String personB)
    {
		PersonNode a = findPerson(root,personA);
		if (a == null)
		{
	    	System.out.print("No person found with name " + personA);
	    	return;
		}
		PersonNode b = findPerson(root,personB);
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
		if ((a.age < 13) || (b.age < 13))
		{
		    System.out.println("At least one person is too young to be in a couple!\n");
			return;
		}
		if ((a.partner != null) && (a.partner != b))
		{
		    System.out.println(a.name + " is currently partnered with " + a.partner.name + " - breaking them up");
	    	a.partner.partner = null;
	    	// if we don't do this, the old partner will still be recorded
	    	// as being in a couple
		}
		if ((b.partner != null) && (b.partner != a))
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

    /** If two people are a couple, separate them. 
     *     personA  -  name of first person
     *     personB  -  name of the second person
     */
    public static void breakCouple(String personA, String personB)
    {
		PersonNode a = findPerson(root,personA);
		if (a == null)
		{
	    	System.out.println("No person found with name " + personA);
	    	return;
		}
		PersonNode b = findPerson(root,personB);
		if (b == null)
		{
	    	System.out.println("No person found with name " + personB);
	    	return;
		}
		if (a == b)
		{
	    	System.out.println("Person A and Person B are the same person!");
	    	return;
		}
		if (a.partner != b)
		{
	    	System.out.println(personA + " is not a couple with " + personB);
	    	return;
		}
		// otherwise we can break them up by setting their partner fields to null
		a.partner = null;
		b.partner = null;
		System.out.println(a.name + " and " + b.name + " have broken up!");
	}
    

    /**
     * Use the sorted binary tree rule to figure out where to insert a new node.
     * Assumes that the fields of the new Node have already been set.
     * Also assumes that we've checked for a duplicate name. 
     * Uses a recursive algorithm to find the right place in the tree.
     * @param  	current		Potential parent node we are checking
     * @param 	newNode		New node we are trying to insert.
     */
    public static void insertNode(PersonNode current, PersonNode newNode)
    {
    	if (newNode.name.compareToIgnoreCase(current.name) < 0)  // new name is earlier in alphabet
    	{
	    	if (current.leftChild == null)
	    		current.leftChild = newNode;  // if there's room, put it as left child
	    	else 
	    		insertNode(current.leftChild,newNode); // otherwise, go to the left to find the correct spot
    	}
		else
		{
	    	if (current.rightChild == null)
	    		current.rightChild = newNode;  // if there's room, put it as right child
	    	else 
	    		insertNode(current.rightChild,newNode); // otherwise, go to the right to find the correct spot	    	
		}
    }


    /** Create some initial values for the tree
     */
    public static void initTree()
    {
		PersonNode newPerson = new PersonNode("FRANK","M",25);
		root = newPerson; 
		peopleCount++;
		newPerson = new PersonNode("JENNY","F",32);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("SOMCHAI","M",19);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("ANNA","F",37);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("MARK","M",25);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("JIM","M",20);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("MARY","F",12);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("ROBERT","M",87);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("SUSAN","F",43);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("WICHIAN","M",17);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("BUNDIT","M",52);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("KATE","F",22);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("LENNY","M",10);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("ARIYA","F",13);
		insertNode(root,newPerson);
		peopleCount++;
		newPerson = new PersonNode("SAM","M",22);
		insertNode(root,newPerson);
		peopleCount++;
		System.out.println("There are currently " + peopleCount + " people in the list");
    }

    /**
     * Print the people in the tree in ascending sorted order
     * This is a recursive function that does an in-order traversal.
     * @param	current		Tree node where we are currently located
     */
    public static void printPeople(PersonNode current)
    {
    	if (current.leftChild != null)
    		printPeople(current.leftChild);
    	current.printInfo();
    	if (current.rightChild != null)
    		printPeople(current.rightChild);
    }

   /**
     * Print the people in the tree in descending sorted order
     * @param	current		Tree node where we are currently located
     */
    public static void printPeopleDescending(PersonNode current)
    {
    	System.out.println("LEFT FOR STUDENT TO IMPLEMENT!");
    }


    /** 
     * Print all the current couples.
     * Uses an in-order traversal (recursive) so the first name of the coupld
     * will be alphabetical. 
     * Uses the printed flag to avoid printing the same couple twice.
     */
    public static void printCouple(PersonNode current)
    {
    	if (current == null)  // removes the need to check before recursive calle
    		return;
    	// go down the left branch
    	printCouple(current.leftChild);
    	// deal with this node
    	if (current.partner != null)
    	{
    		if (current.printed == false)
			{
				System.out.println(current.name + " is partnered with " + current.partner.name);
				current.partner.printed = true;  // so we won't print twice
			}
			else // don't print, but reset the printed flag is necessary
			{
				current.printed = false;
			}
    	}
    	// go down the right branch
    	printCouple(current.rightChild);
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
      	initTree();
      	while (option != 10)
      	{
	  		System.out.print("\n  1 -  Make a couple\n");
	  		System.out.print("  2 -  Print all couples\n");
	  		System.out.print("  3 -  Break up a couple\n");
	  		System.out.print("  4 -  Print all people's names (ascending sort)\n");
	  		System.out.print("  5 -  Print all people's names (descending sort)\n");
	  		System.out.print("  6 -  Add a new person\n");
	  		System.out.print(" 10 -  Exit\n");	
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
	  			printCouple(root);
	  		}
	  		else if (option == 3)
	  		{
	  			name1 = promptForString("\nFirst person's name?");
	  			name2 = promptForString("Second person's name?");
	  			breakCouple(name1,name2);
	  		}
	  		else if (option == 4)
	  		{
	  			System.out.print("\nHere is the current list of names (ascending sort):\n");
	  			printPeople(root);
	  			System.out.print("[END OF LIST]\n");
	  		}
	  		else if (option == 5)
	  		{
	  			System.out.print("\nHere is the current list of names (descending sort):\n");
	  			printPeopleDescending(root);
	  			System.out.print("[END OF LIST]\n");	  			
	  		}
	  		else if (option == 6)
	  		{
	  			name1 = promptForString("\nNew person's name?");
	  			gender = promptForString("New person's gender?");
	  			name1 = name1.toUpperCase();
	  			gender = gender.toUpperCase();
	  			String temp = promptForString("New person's age?");
	  			int age = Integer.parseInt(temp);  // will crash if the user types a non-int
	
	      	System.out.println("LEFT FOR THE STUDENT TO IMPLEMENT!");
	      	}
	  		else if (option != 10)
	  		{
	  			System.out.print("INVALID OPTION NUMBER!\n");
	  		}
	  	}
	}
}
