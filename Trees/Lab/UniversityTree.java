/*  UniversityTree.c
 *
 *  Partially complete program giving students the chance to work with trees
 *  Created by Sally Goldin, 1 July 2022 for AiCE Warp Data Structures competency
 *  Modified by YOUR NAME HERE
 */

import java.util.Scanner;

/**
 * Class to demonstrate the basics of building and searching a 
 * generic tree
 */
public class UniversityTree
{

  /** object to use for getting terminal input */
  private static Scanner scan = new Scanner(System.in);


  /** Ask the user a question and get a string as a reply
   * @param  prompt --  Question or message
   * @return  answer from the user
   */
  private static String promptForString(String question)
  {
    System.out.print(question +" ");
    String input = scan.nextLine();
    return input;
  }

  /** 
   * Find a node based on its title. 
   * This code uses a recursive algorithm (preOrder traversal) which we'll study next week.
   * @param current     	Tree node we're looking at now
   * @param searchTitle		Title of the node we are looking for
   * @return the matching node, or null if not found
   */
  private static UniTreeNode findNode(UniTreeNode current, String searchTitle)
  {
    UniTreeNode found = null;
    if (current.title.equalsIgnoreCase(searchTitle))
	found = current;
    else
    {
      int i;
      for (i = 0; i < current.childCount; i++)
      {
	found = findNode(current.children[i],searchTitle);
	if (found != null)   /* got it! */
	  break;
      }
    }
    return found;
  }

  /** Add a node as the child of another node.
   * If the parent node's list of children is full, return 0 for error.
   * If the parent node is the wrong type (should be one less than current type), return 0
   * Otherwise return 1 for success
   * @param parent     	Parent node
   * @param child      	Child node
   * @return 1 for success, 0 if error
   */
  private static int insertChildNode(UniTreeNode parent, UniTreeNode child)
  {
    int result = 1;
    if (parent.type != (child.type - 1))
    {
      System.out.println("Parent is the wrong type for child!");
      result = 0;
    }
    else if (parent.childCount == UniTreeNode.MAX_CHILDREN)
    {
      System.out.println("Parent has no room for more children");
      result = 0;
    }
    else
    {
      parent.children[parent.childCount] = child;
      parent.childCount++;
      child.parent = parent;
    }
    return result;
  }


  /** Add a few nodes to the tree
   * so we have something to print.
   */
  private static void initTree(UniTreeNode root)
  {	
    UniTreeNode node;		// used for creating other nodes
    UniTreeNode parentNode;     // used in initialization
    /* add a few schools 
     * Find the full list here: https://www.kmitl.ac.th/current-students - Academic Divisions 
    */
    node = new UniTreeNode("School of Engineering",UniTreeNode.SCHOOL);
    insertChildNode(root,node);
  
    node = new UniTreeNode("School of Science",UniTreeNode.SCHOOL);
    insertChildNode(root,node);
  
    /* add a few departments */
    parentNode = findNode(root,"School of Engineering");
    if (parentNode != null)
    {
      node = new UniTreeNode("Mechanical Engineering",UniTreeNode.DEPARTMENT);
      insertChildNode(parentNode,node);
    
      node = new UniTreeNode("Computer Engineering",UniTreeNode.DEPARTMENT);
      insertChildNode(parentNode,node);
    }
  
    parentNode = findNode(root,"School of Science");
    if (parentNode != null)
    {
      node = new UniTreeNode("Chemistry",UniTreeNode.DEPARTMENT);
      insertChildNode(parentNode,node);
    
      node = new UniTreeNode("Physics",UniTreeNode.DEPARTMENT);
      insertChildNode(parentNode,node);
    }
     
    /* add a program */
    parentNode = findNode(root,"Computer Engineering");
    if (parentNode != null)
    {
      node = new UniTreeNode("CIE Program",UniTreeNode.PROGRAM);
      insertChildNode(parentNode,node);
    }
  }

  /** Get the information, then add a new node into the tree
   * Need to know the details of the node, plus what its parent 
   * should be.
   * @param root	Root of the tree, needed to find the parent
   */
  private static void addNewNode(UniTreeNode root)
  {
    String title;
    String parentTitle;
    String typeString;
    int typeVal;
    title = promptForString("Title for new node? ");
    typeString = promptForString("Type for new node? (1=school, 2=department, 3=program) ");
    try 
    {
      typeVal = Integer.parseInt(typeString);
    }
    catch (NumberFormatException e)
    {
      System.out.println("Invalid type - must be an integer, 1 to 3");
      return;
    }
    if ((typeVal < 1) || (typeVal > 3))
    {
      System.out.println("Invalid node type!\n");
      return;
    }
    parentTitle = promptForString("Title of parent node? ");
    System.out.println("NOT YET IMPLEMEMENTED");
    // ADD CODE HERE TO:
    //   -- look up the parent node
    //   -- if successful, create the child node
    //   -- set the title and type of the child node
    //   -- add the child to the parent
    // Don't forget to check the results of each step
    // For instance, if the parent doesn't exist, you should
    // give an error message and return.
  }


  /* Get the information about the node to remove
   * Search the tree to find it, then remove it. 
   * CAREFUL - if the node has children, you need to remove those
   * first!
   */
  private static void removeNode(UniTreeNode root)
  {
    String title;
    title = promptForString("Title for node to remove? ");
    System.out.println("NOT YET IMPLEMEMENTED");
    // ADD CODE HERE TO:
    //   -- Look up the node to be removed
    //   -- If found, see if it is a leaf (childCount == 0)
    //      If not, print an error telling the user they must
    //      delete the children first and return
    //   -- Otherwise, use the parent link to find the parent
    //   -- Remove the node from the parent array -- you might have to move the other
    //      children earlier in the array to fill the "hole"
    //   -- Delete 1 from the parent's childCount
}

  /** Main function creates the root node and adds
   * some nodes into the tree, then displays a menu with
   * functions, some of which the student is required to implement.
   */
  public static void main(String args[])
  {
    UniTreeNode root;		// root node of our tree
    int option = 0;		// menu option
    /* start by adding some items to the tree */
    root = new UniTreeNode("KMITL",UniTreeNode.UNIVERSITY);   // create the root 
    initTree(root);
  
    System.out.println("Here is the starting tree for KMITL:");
    root.printNode();
    while (option != 10)
    {
      System.out.println("\nAvailable options:");
      System.out.println("\t1 Print current tree");
      System.out.println("\t2 Add new tree node");
      System.out.println("\t3 Remove tree node");
      System.out.println("\t10 Exit the program");
      String optionString = promptForString("Enter option: ");
      try
      {
	option = Integer.parseInt(optionString);
      }
      catch (NumberFormatException e)
      {
	System.out.println("Please enter a numeric option!");
	continue;
      }
      switch (option)
      {
	case 1:
	  root.printNode();
	  break;
	case 2:
	  addNewNode(root);  // see partially implemented function above main
	  break;
	case 3:
	  removeNode(root);  // see partially implemented function above main
	  break;
	case 10:
	  System.out.println("Goodbye!\n");
	  System.exit(0);
	default:
	  System.out.println("Illegal option. Please try again!\n");
      }
    }
  }
}
