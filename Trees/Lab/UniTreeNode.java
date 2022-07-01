/* UniTreeNode.java
 *  
 * Part of the UniversityTree demo
 * Defines a data-only class that represents a tree node in our
 * university tree structure.
 * Created by Sally Goldin, 1 July 2022
 * Students should not need to change this.
 */

/**
 * Represents a node in a tree holding the structure of a university.
 */
public class UniTreeNode
{

  public static final int UNIVERSITY = 0;
  public static final int SCHOOL = 1;
  public static final int DEPARTMENT = 2;
  public static final int PROGRAM = 3;

  /** Maximum number of children a node can have */
  public static final int MAX_CHILDREN = 20;
  
  /** for printing the node type */
  public static String nodeTypeTitles[] = new String[]{"University","School","Department","Program"};
  
  /** Title of the node */
  public String title;
  
  /** Type of the node */
  public int type;
  
  /** Parent of the node */
  public UniTreeNode parent;
  
  /** Array of children */
  public UniTreeNode children[] = new UniTreeNode[MAX_CHILDREN];
  
  /** How many children currently? */
  public int childCount = 0;
  
  /** 
   * Constructor creates a new node and sets its title and type
   */
  public UniTreeNode(String nodeTitle, int nodeType)
  {
    title = nodeTitle;
    type = nodeType;
  }
  
  /**
   * Method to print a tree node along with spacer
   * that indicates its type
   */
  public void printNode()
  {
    int i;
    for (i = 0; i < type; i++) System.out.print("----"); 
    System.out.println(" " + title + " (" + nodeTypeTitles[type] + ")");
    if (childCount > 0)
    {
      for (i = 0; i < childCount; i++)
	children[i].printNode();
    }
  }
}