/**
 *  HashDictionary.java
 * 
 *  Main class for laboratory exercise using a hash table to build a dictionary.
 * 
 *  Created by Sally Goldin, 15 July 2022, for AiCE Warp
 */ 
import java.util.Hashtable;
import java.util.Scanner;

public class HashDictionary
{
   /** class instance for reading the input file */
   private static TextFileReader reader = new TextFileReader();

   /** object to use for getting terminal input */
   private static Scanner scan = new Scanner(System.in);

   /** Hashtable to serve as our dictionary */
   private static Hashtable<String,DictionaryEntry> dictionary = new Hashtable<String,DictionaryEntry>();

   /** 
    * Ask the user a question and get a string as a reply
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
    * Read word file and construct the dictionary.
    * @param  filename    Name of file to read
    * Returns 1 if successful, 0 for I/O error.
    */
   public static int buildDictionary(String filename)
   {
      DictionaryEntry entry = null;
      String line;
      int returnVal = 1;
      int wordCount = 0;
      if (!reader.open(filename)) 
      {
         System.out.println("Error opening word file '" + filename + "'\n");
         return 0;
      }
      // otherwise read each line and process it
      while (((line = reader.getNextLine()) != null) &&
           (returnVal == 1))
      {
         int delim = line.indexOf("|");
         if (delim >= 0)
         {
            String word = line.substring(0,delim);
            String definition = line.substring(delim+1);
            entry = new DictionaryEntry(word,definition);
            dictionary.put(word,entry);
            wordCount++;
         }
      }  /* if no delimiter, just skip the line */
      reader.close();
      System.out.println("Stored " + wordCount + " words in the dictionary\n");
      return returnVal;
   }

   /** 
    * Look up a word and 
    * print its definition(s) for a word, or print 'Not Found'
    * if not in the dictionary. 
    * @param  word          -   Word to look up
    */
   private static void printDefinition(String word)
   {
      DictionaryEntry entry = null;
      entry = dictionary.get(word);
      if (entry == null)
      {
         System.out.println("Word '" + word + "' not found in the dictionary\n");
      }
      else
      {
         entry.printInfo();
      }
   }  

   /**
    * Main function presents menu and controls logic
    */
   public static void main(String args[])
   {
      int status = buildDictionary("wordlist.txt");
      if (status == 0)
      {
         System.out.println("Cannot read file\n");
         System.exit(1);
      } 
      /* now loop, allowing lookup or addition of new words */
      while (true)
      {
         int option = 0;
         String input;
         String word;
         System.out.println("\nAvailable operations: ");
         System.out.println("\t1 - Look up a word in the dictionary");
         System.out.println("\t2 - Add a word to the dictionary");
         System.out.println("\t3 - Add an additional definition to an existing word");
         System.out.println("\t4 - Exit the program");
         input = promptForString("Option? ");
         try
         {
            option = Integer.parseInt(input);
         }
         catch (NumberFormatException nfe)
         {
            System.out.println("Please enter a valid integer between 1 and 4\n");
            continue;
         }
         if (option == 1) 
         {
            word = promptForString("Find definition for what word? ");
            printDefinition(word);
         }
         else if (option == 2)
         {
            System.out.println("FOR IMPLEMENTATION BY THE STUDENT!\n");
            // STUDENT TASK ONE
            // Add code here to ask for word and definition, then
            // add to the dictionary
         }
         else if (option == 3)
         {
            System.out.println("FOR IMPLEMENTATION BY THE STUDENT!\n");
            // STUDENT TASK TWO
            // Add code here to add an additional definition to an existing
            // word. NOTE you may need to modify the structure of
            // DICT_ENTRY_T in order to complete this task
         }
         else if (option == 4)
         {
            break;
         }
         else 
         {
            System.out.println("Please enter a value between 1 and 4!\n");
         }
      }
   }

}