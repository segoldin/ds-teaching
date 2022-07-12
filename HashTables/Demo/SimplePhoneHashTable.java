/**
 *  SimplePhoneHash.java
 *
 *  This is a very simple example showing how hash tables work.
 *  In fact Java has built-in classes for hash tables, but this program
 *  lets you look "under the hood" to see the basics of how they work
 *  Created by Sally Goldin for Warp Data Structures competency, 12 July 2022
 */
 
 
import java.util.Scanner;

/**
 * Implements a hash table using phone numbers as the keys.
 * Treats each phone number as a set of digits. Adds the digits then
 * uses mod to figure out which element of the hash table to use for 
 * storing the item.
 */
public class SimplePhoneHashTable
{
    private static final int TABLESIZE = 11;
    
    /** keep track of how many collisions occur */
    private static int collisionCount = 0;

    /** object to use for getting terminal input */
    private static Scanner scan = new Scanner(System.in);

    /** This array is the actual hash table */
    /* A real hash table would be much bigger, of course */
    public static Customer hashTable[] = new Customer[TABLESIZE];

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
    
    /**
     * Hash function turns a key (a phone number string) into
     * a value which is used to index the hash table
     * @param    phoneNo     Key value
     * @return   integer between 0 and TABLESIZE-1 telling us where
     *              to store this Customer
     */
     private static int phoneHashFunction(String phoneNo)
     {
        int digitVal;
        int digitSum = 0;
        char digitChars[] = phoneNo.toCharArray();
        for (char c : digitChars)
        {
            digitVal = Character.digit(c,10);
            if (digitVal >= 0)   // returns -1 for illegal digits
                digitSum += digitVal;
        }
        return digitSum % TABLESIZE;   // make it fit in the range
     }
     
     /**
      * Insert a customer into the hash table.
      * @param customer   Customer object to insert
      * @return true for success, false if there's a collision
      */
      public static boolean hashInsert(Customer customer)
      {
        boolean success = true;
        int hashIndex = phoneHashFunction(customer.phone);
        System.out.println("Hash function returns " + hashIndex);
        if (hashTable[hashIndex] == null) // slot is empty
        {
            hashTable[hashIndex] = customer;
        }
        else 
        {
            collisionCount++;
            success = false;
        }
        return success;
      }
     
         /**
      * Look up a customer into the hash table.
      * @param phone   Phone number to use as search key
      * @return found customer, or null if not found
      */
      public static Customer hashLookup(String phone)
      {
        int hashIndex = phoneHashFunction(phone);
        Customer customer = hashTable[hashIndex];
        if ((customer != null) && (customer.phone.equals(phone)))
            return customer;
        else
            return null;
      }
     
    /** 
     * Main function lets us store and retrieve Customers.
     */
     public static void main(String args[])
     {
        Customer customer;   /* use for creating customers */
        String phone;
        String name;
        String gender;
        int age;
        String input;
        int option = 0;      /* for menu */
        System.out.println("Welcome to Sally Supermarket!");
      	while (option != 10)
      	{
	  		System.out.print("\n  1 -  Add a new customer\n");
	  		System.out.print("  2 -  Look up a customer and print their data\n");
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
                phone = promptForString("\n    Customer phone number (10 digits starting with 0)? "); 
	  			name = promptForString("    Customer's name? ");
                gender = promptForString("    Customer's gender (M=male, F=female, N=not specified)? ");
                input = promptForString("    Customer's age? ");
                try 
                {
                    age = Integer.parseInt(input);
                }
                catch (NumberFormatException nfe)
                {
                    System.out.println("Invalid integer!");
                    continue;
                }
                customer = new Customer(phone,name,gender,age);
                System.out.println("Created new customer!");
                customer.printInfo();
                System.out.println("About to insert in hash table");
                boolean result = hashInsert(customer);
                if (result)
                {
                    System.out.println("Successfully inserted new customer");
                }
                else
                {
                    System.out.println("Collision! New customer not inserted!");
                }
                
            }
	  		else if (option == 2)
	  		{
	  			phone = promptForString("\n    Customer phone number (10 digits starting with 0)? ");
	  			customer = hashLookup(phone);
	  			if (customer == null)
	  			{
                    System.out.println("Customer with phone number " + phone + " not found");
	  			}
	  			else
	  			{
                    System.out.println("Found customer!");
                    customer.printInfo();
	  			}
	  		}
	  		else if (option != 10)
	  		{
	  			System.out.print("INVALID OPTION NUMBER!\n");
            }
        }
     System.out.println("With a table size of " + TABLESIZE + " we had " + collisionCount + " collisions");
     System.out.println("Sayonara!");
     }
}
