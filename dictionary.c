/****************************************************************************
 * dictionary.c
 *
 * Laufenshoen
 *
 * Implements a dictionary's functionality.
 
       
    // e–>member and (*e).member
    //or
    // pointerToNode->member
    
    ./speller ~cs50/pset6/dictionaries/small ~cs50/pset6/texts/austinpowers.txt
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 * TODO case-insensitivity
 */
bool check(const char* word)
{
    node* currNode = myTrie.root;
    int length = strlen(word) + 1;
    for (int depth = 0; depth < length; depth++)
    {
        //Get a number value for the letter.
        int letter = word[depth];
        if (letter == 0)                               //letter is '\0'
        {
            if (currNode->leaf == true)
            {
                return true;
            }
        }
        else if (letter == 39)                         //letter is '
        {
            if (currNode->characters[26] == NULL)
            {
                return false;  
            }
            else
            {
                currNode = currNode->characters[26];
            }   
        }
        else                                           //letter isAlpha
        {
            int index;
            if (letter >= 97)
            {
                index = letter - 'a';  
            }
            else
            {
                index = letter - 'A';
            }
            if (currNode->characters[index] == NULL)
            {
                return false;  
            }
            else
            {
                currNode = currNode->characters[index];
            } 
        } 
    }
    return false;
}

/**
 * Creates another node with an array of 27 indexes and a leaf inidicator.
 * NOT SURE WHY THERE IS THE (node *)
 */
 
node* getNode(void)
{
    node* NewNode = (node *)malloc(sizeof(node));
    NewNode->leaf = false;
    for ( int i = 0; i < 27; i++)
    {
        NewNode->characters[i] = NULL;
    }
    return NewNode;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO Run Valgrind and doa gdb run through checking variables.
    
    //Open the dictionary file.
    FILE* dict = fopen(dictionary,"r");
    if (!dict)
    {
        return false;
    }
   
    //Init currNode
    myTrie.count = 0;
    myTrie.root = getNode();
    node* currNode = myTrie.root;
    
    char word[LENGTH + 2];
    
    while (fgets(word, LENGTH + 2, dict) != NULL)
    {   
        int length = strlen(word);
        for (int depth = 0; depth < length; depth++)
        {
            //Get a number value for the letter.
            int letter = word[depth];
            if (letter == 10)                               //letter is '\n'
            {
                currNode->leaf = true;
            }
            else if (letter == 39)                          //letter is '
            {
                if (currNode->characters[26] == NULL)
                {
                    currNode->characters[26] = getNode();
                    currNode = currNode->characters[26];  
                }
                else
                {
                    currNode = currNode->characters[26];
                }   
            }
            else                                            //letter isAlpha
            {
                int index = letter - 'a';
                if (currNode->characters[index] == NULL)
                {
                    currNode->characters[index] = getNode();
                    currNode = currNode->characters[index];  
                }
                else
                {
                    currNode = currNode->characters[index];
                } 
            } 
        }
        myTrie.count++;
        currNode = myTrie.root; 
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    unsigned int dictCount = myTrie.count;    
    return dictCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 void freeNode(node* thisNode)
 {
    for (int i = 0; i < 27; i++)
    {
        if (thisNode->characters[i] != NULL)
        {
            freeNode(thisNode->characters[i]);
        }
    }
    free(thisNode);
 }
 
bool unload(void)
{
    // TODO
    freeNode(myTrie.root);
    //printf("%i", freeCount);
    return true;
}
