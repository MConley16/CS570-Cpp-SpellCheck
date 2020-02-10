/* spellcheck.C
 * author: Melissa Conley misc0222 818890729
 * CS570 Prof. Roch
 * desc: Creates dictionary tree from words contained in the dictionary file
 *	 Searches for words from the spellcheck text file in the dictionary tree - if 
 *      they are found, they are spelled correctly
 *	 Contains main method that tests and implements the class DictEntry and 
 *       methods insert and find
 */
 
 #include <stdio.h>
 #include <iostream>
 #include <fstream>
 #include <string.h>
 #include "dictionary.h"
 
 using namespace std;
 
 int main(int argc, char **argv)
 {
 	if(argc < 3)
	{
		cout << "Please enter 2 arguments: text file to be spell checked "
		<< "first and dictionary source file second\n";
		exit(1);
	}
	
	//Open dicitonary source file
	ifstream dictFile;		
	dictFile.open(argv[argc-1]);		
	if(!dictFile)
	{
		cerr << "File not found or unable to open " << argv[argc-1] << "\n";
		exit(1);
	}
	
	//Variables for building dictionary tree
	const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
	string currentLine1a;
	DictEntry *root;
	root = new DictEntry();
	for(int i=0; i<SIZE; i=i+1)	//Fill root's child pointers
		{
			root->child[i] = new DictEntry;	//Declare pointees
		}
	
	//Parse through the dictionary source file one line at a time and 
	//create a dictionary tree from the words within it
	while(getline(dictFile, currentLine1a))
	{
		//Convert current line from string to char pointer for 
		//the strtok function
		//strcpy(currentLine1b, currentLine1a.c_str());
		char * currentLine1b = new char [currentLine1a.length()+1];
		strcpy (currentLine1b, currentLine1a.c_str());
		
		//Tokenize the current line
		char *token1;
		token1 = new char;
		token1 = (char *)strtok(currentLine1b, separators);
		while(token1 != nullptr)
		{
			insert(root,token1,token1);
			//get the next token from the currentLine1 buffer
			token1 = strtok(NULL, separators);
		}
	}
	dictFile.close();
	
	//Open text file to spell check
	ifstream textFile;
	textFile.open(argv[argc-2]);
	if(!textFile)
	{
		cerr << "File not found or unable to open " << argv[argc-2] << "\n";
		exit(1);
	}
	
	string currentLine2a;
	char *currentLine2b;
	ResultType spellcheck;
	
	//Parse through the words in the text file to see if they match any 
	//words in the dicitonary tree to see if they are mispelled
	while(getline(textFile,currentLine2a))
	{
		//Convert current line from string to char pointer 
		//for the strtok function
		char * currentLine2b = new char [currentLine2a.length()+1];
		strcpy (currentLine2b, currentLine2a.c_str());
		
		char *token2 = (char*)strtok(currentLine2b,separators);
		while(token2 != nullptr)
		{
			spellcheck = find(root,token2,token2);
			//Print misspelled words to standard output
			if(spellcheck == MISSPELLED)
			{
				cout << token2 << "\n";
			}
			token2 = strtok(NULL, separators);
		}
	}
	textFile.close();
}
