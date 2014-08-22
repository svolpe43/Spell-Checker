/****************************************************************************
 * dictionary.h
 *
 * Laufenshoen
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

struct trie myTrie;
//freeCount++;
//mallocCount;

typedef struct node
{
    bool leaf;
    struct node* characters[27];
} node;

typedef struct trie
{
    int count;
    node* root;
} trie;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Creates another node with an array of 27 indexes and a leaf inidicator.
 */
 
node* getNode(void);



#endif // DICTIONARY_H
