/* dictionary.h
 * author: Melissa Conley misc0222 818890729
 * desc: Contains signatures for class DictEntry and 
 * methods insert and find
 */
 
#ifndef DICTIONARY_H
#define DICITONARY_H

const int SIZE = 27;
enum ResultType {CORRECT,MISSPELLED};

//Class DictEntry: defines nodes to be inserted into the dictionary tree
class DictEntry
{
	public:
	char key;			//The letter stored in the node
	bool isEndOfWord = false;
	//array of 27 pointers that point to other dictentries:
	DictEntry *child[SIZE];		
	
};

//Method insert: adds tokens to the dictionary tree
//args: dictNode-current node, characters-chars left to parse through in targetword, 
//targetword-token being added to tree
void insert(DictEntry *dictnode, const char *characters, 
const char * targetword =nullptr);

//Method find: searches the tree recursively for the targetword
//args: dictNode-current node, word-chars left to parse through in targetword, 
//targetword-token being searched for
ResultType find(DictEntry *dictnode, const char *word,
const char *targetword=nullptr);


#endif
