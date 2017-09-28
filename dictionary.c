/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * load implementation based on: http://code.geeksforgeeks.org/index.php
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "dictionary.h"



/**
 * Returns true if word is in dictionary else false.
 */
bool check(struct TrieNode *rootnode, char* wordP)
{
	int level;
	int length = strlen(wordP);
	int index;
    struct TrieNode *pCrawl = rootnode;
    char CurrentChar;

	for (level = 0; level < length; level++)
	{
		// if upper case, converts to lower case
		CurrentChar = ( islower(wordP[level]) ) ? wordP[level] : ( wordP[level] + 32 );
		
		index = CHAR_TO_INDEX(CurrentChar);
		
		// checks for apostrophe
		index = ( index >= 0 && index <= 25 ) ? index : 26;

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isLeaf);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * Implementation by inserting Nodes on Trie
 * 
 * Creates extendable-length trie.
 */
bool load(struct TrieNode *rootnode, const char* dictionary, int * wordcount)
{
    // creates root Node
    struct TrieNode *root = rootnode;
    
    // temporary stores each dictionary word
    char word[LENGTH];
    
    // to read from dictionary
    char c;
    int i = 0;

    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload(rootnode);
        return 10;
    }
    
    // control
//    printf("Results of reading IN:\n");
    
    // reads 1 character from dictionary
    while ( (c = getc(fp) ) != EOF )
    {
        // reads until end-of-line
        if ( c != '\n' )
        {
            // stores 1 word
            word[i] = c;
            i++;
        }
        // when end-of-line reached
        else
        {
            word[i] = '\0';
            
            // control
//            for ( int a = 0; a < i; a++)
//            	printf("%c", word[a]);
//            printf(":end\n");
            
            insert(root, word);
            *wordcount += 1;
            i = 0;
        }
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(int * wordcount)
{
    // returns wordcount calculated in 'load'
    return *wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(struct TrieNode * rootnode)
{
    struct TrieNode *pCrawl = rootnode;

	// checking thru children[i]
	for ( int i = 0; i < ALPHABET_SIZE; i++ )
		if ( pCrawl->children[i] )
			unload(pCrawl->children[i]);
	
	free(pCrawl);
	
	return true;
}

/**
 * Creates new trie node (initialized to NULLs)
 */
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = NULL;

	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	if (pNode)
	{
		int i;

		pNode->isLeaf = false;

		for (i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	}

	return pNode;
}

/**
 * If not present, inserts key(word from dictionary) into trie
 * If the key is prefix of trie node, just marks leaf node
 */
void insert(struct TrieNode *root, const char *word)
{
	int level;
	int length = strlen(word);
	int index;

	struct TrieNode *pCrawl = root;

	
	// control
//	printf("Word being inserted:");
	
	for (level = 0; level < length; level++)
	{
		// control
//		printf("%c", word[level]);
		
		index = CHAR_TO_INDEX(word[level]);
		
		// checks for apostrophe
		index = ( index >= 0 && index <= 25 ) ? index : 26;
		
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isLeaf = true;
	
	// control
//	printf(":end\n");
}