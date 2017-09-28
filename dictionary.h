/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// default dictionary
#define DICTIONARY "dictionaries/large"

// maximum length for a word + '\0' character
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45+1

// ARRAY_SIZE == number of keys
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols) + apostrophe
#define ALPHABET_SIZE (26+1)

// Converts key's current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node 
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isLeaf is true if the node represents
	// end of a word
	bool isLeaf;
};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(struct TrieNode *rootnode, char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(struct TrieNode *rootnode, const char* dictionary, int * wordcount);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(int * wordcount);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(struct TrieNode * rootnode);

/**
 * Returns new trie node (initialized to NULLs)
 */
struct TrieNode *getNode(void);

/**
 * If not present, inserts key(word from dictionary) into trie
 * If the key is prefix of trie node, just marks leaf node
 */
void insert(struct TrieNode *root, const char *word);
 
#endif // DICTIONARY_H
