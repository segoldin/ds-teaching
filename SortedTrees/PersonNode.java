/** 
 * PersonNode.java
 * 
 * Class to represent one person in the "couples" world, with left and right children
 * so they can be build into a sorted binary tree.
 *
 * Created by Sally Goldin for AiCE Warp Data Structures competency, 10 July 2022
 * This version shows suggested solutions to the lab tasks.
 */

public class PersonNode
{

    /** Each person has a name */
    public String name;

    /** Each person has a gender */
    public String gender;
    
    /** Each person has an age */
    public int age;
    
    /** Each person may have a partner, which is an instance of another CoupleDemo person */
    public PersonNode partner; 
    
    /** Point to left child (with names earlier in the alphabet) */
    public PersonNode leftChild;
    
    /** Point to right child (with names later in the alphabet) */
    public PersonNode rightChild;
       
    /** Keep track if printed yet */
    public boolean printed;

   /**
     * Constructor creates a new person
     * and sets its values
     */
    public PersonNode(String personName, String personGender,int personAge)
    {
      name = personName.toUpperCase();
      gender = personGender.toUpperCase();
      age = personAge;
      printed = false;
    }

  /**
   * Print the current person node information
   */
    public void printInfo()
    {
      System.out.println(name + "\t(" + gender + ", age " + age + ")"); 
    }
}
