/**
 * Customer.java
 *
 * Data class to store in the hash table.
 * Represents a customer with a phone number (key), name, gender and age.
 * Created by Sally Goldin for Warp Data Structures competency, 12 July 2022
 */
 public class Customer
  {
    /** keep track of how many customers created */
    public static int customerCount = 0;
  
    /** ID is the counter when this customer was created */
    public int ID;
    
    /** phone number - this will be the key */
    public String phone;
    
    /** Customer name */
    public String name;
    
    /** Gender */
    public String gender;
    
    /** Customer's age */
    public int age;
    
    /** Constructor to create a new customer and set its values */
    public Customer(String phoneNumber, String customerName, String customerGender, int customerAge)
    {
        customerCount++;
        ID = customerCount;
        phone = phoneNumber;
        name = customerName;
        gender = customerGender;
        age = customerAge;
    }
 
    /** Method to print this customer */
    public void printInfo()
    {
        System.out.println("Customer #" + ID);
        System.out.println("    " + phone + "  [" + name + "   " + gender + "   Age: " + age +"]"); 
    }
    
 
 }
 
 
