/* dictionary.c
 * author: Melissa Conley misc0222 818890729
 * desc: Defines methods insert and find
 */
 
#include <stdlib.h> 
#include <iostream>
#include "dictionary.h"

using namespace std;
 
void insert(DictEntry *dictNode, const char *characters, const char *targetword)
{
	//Once the token is completely parsed through, 
	//indicate the last letter as the end of word
 	if(*characters == '\0')
	{
		dictNode->isEndOfWord = true;
		//Addition to the tree is complete
		return;
	}

	//Convert the letter to an index of a child node
	int index = (int)*characters;
	
	//If char is an uppercase letter:
	if(index >= 65 && index <= 90)
	{
		index = index - 65;
	}
	//If char is a lowercase letter:
	else if(index >= 97 && index <= 122)
	{
		index = index - 97;
	}
	//If char is ':
	else if(index == 39)
	{
		index = 26;
	}
	else
	{
		return;
	}
	
	//If node already has the current letter as a child, move 
	//on to that child through a recursive call
	if(dictNode->child[index]->key != '\0')
	{
		insert(dictNode->child[index], characters+1, targetword);
	}
	//If not, add a child node with the current letter
	else
	{
		DictEntry *newDictNode;
		newDictNode = new DictEntry();
		newDictNode->key = *characters;
		int i;
		for(i=0; i<SIZE; i=i+1)
		{
			newDictNode->child[i] = new DictEntry;	//Declare pointees
		}
		dictNode->child[index] = newDictNode;
		//Move on to the newly added child through a recursive call
		insert(newDictNode, characters+1, targetword);
	}
	
	return;
}

ResultType find(DictEntry *dictNode, const char* word, const char *targetword)
{
	//Once completely parsed through the word:
	if(*word == '\0')
	{
		//If the targetword is found in the tree, it is correctly spelled:
		if(dictNode->isEndOfWord)
		{
			return CORRECT;
		}
		//If it does not exist in the tree, it is misspelled:
		else
		{
			return MISSPELLED;
		}
	}
	
	//Convert the letter to an index of a child node
	int index = (int)*word;
	
	//If char is an uppercase letter:
	if(index >= 65 && index <= 90)
	{
		index = index - 65;
	}
	//If char is a lowercase letter:
	else if(index >= 97 && index <= 122)
	{
		index = index - 97;
	}
	//If char is ':
	else if(index == 39)
	{
		index = 26;
	}

	//If node has the current letter as a child, keep searching:
	if(dictNode->child[index]->key != '\0')
	{
		find(dictNode->child[index], word+1, targetword);
	}
	//If the current letter is not found, the targetword does not exist:
	else
	{
		return MISSPELLED;
	}

}






