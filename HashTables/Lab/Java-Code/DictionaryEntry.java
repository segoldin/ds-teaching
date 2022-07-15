/**
 * DictionaryEntry.java
 *
 *   Data class to hold information about a word and its definition(s)
 *
 * Created by Sally Goldin, 15 July 2022
 */
public class DictionaryEntry
{
	
	/** The word */
	private String word;

	/** One definition */
	private String definition;

	/** 
	 * Constructor creates a new entry, setting the member variables
	 */
	public DictionaryEntry(String theWord, String theDefinition) 
	{
		word = theWord;
		definition = theDefinition;
	}

	/** Getter for the word */
	public String getWord() 
	{
		return word;
	}

	/** Getter for the definition */
	public String getDefinition()
	{
		return definition;
	}

	/** print the information in the entry */
	public void printInfo()
	{
		System.out.println("\nWord: "+ word);
		System.out.println("Definition: " + definition + "\n");
	}
}
