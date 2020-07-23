// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

unsigned long dictionarySize = 0; //total amount of words

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //int word_hash;
    //// get hash value for the input word
    //word_hash = hash(word);
    //
    //for (node *cursor = table[word_hash]; cursor != NULL; cursor = cursor->next) // access linked list at that index in the hash table
    //{
    //    if (strcasecmp(cursor->word, word) == 0) // traverse linked list, looking for the word (strcasecmp)
    //        return true;
    //}
    //
    //return false;

    char tmpWord[strlen(word) + 1];
    strcpy(tmpWord, word);
    char *p = tmpWord;
    for ( ; *p; ++p) *p = tolower(*p);

    unsigned long word_hash = hash(tmpWord);
    node *cursor = table[word_hash];

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, tmpWord) == 0)
            return true;

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
   //int sum = 0;
   //int index = 0;
   //while(word[index] != '\0')
   //{
   //    sum+=word[index];
   //    index++;
   //}
   //return sum % MAX_BUCKETS;

    unsigned int count;
    unsigned int hashValue = 0;

    for(count = 0; word[count] != '\0'; count++)
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;

    return (hashValue % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //function takes a string and returns an index

    //open dictionary file
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL) //check if return value is NULL
        return false;

    char *tmp_word = malloc((LENGTH + 1) * sizeof(char)); //allocate memory for a string to keep the input word from a dictionary
    int index; // index for a hash table

    // read strings from file one at a time
    while (fscanf(dict, "%s", tmp_word) != EOF) //repeat until fscanf returns EOF
    {
        // create a new node for each word -- use chaining method for resolving collisions
        node *newWord = malloc(sizeof(node)); //use malloc to allocate memory to store a new word in a node

        if (newWord == NULL) //check if return valus is NULL
            return false;

        newWord->next = NULL; // set up null pointer for a new node
        strcpy(newWord->word, tmp_word); //copy word into node using strcpy

        // hash word to obtain a hash value
        index = hash(tmp_word);

        // insert node into hash table at that location
        if (table[index] == NULL) // if hashtable is empty at index, then insert
        {
            table[index] = newWord;
        }
        else //if a node is already attached
        {
            newWord->next = table[index]; // point to the head
            table[index] = newWord; //head to point on a new node
        }
        dictionarySize++; //adding new word to a total amount
    }

    free(tmp_word);
    //close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (dictionarySize >= 1)
        return dictionarySize;

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        //node *tmp = table[i]; //get first node[i] to free
        //node *cursor = table[i];
        //while (cursor != NULL)
        //{
        //    cursor = cursor->next;
        //    free(tmp);
        //}
    }
    return true;
}
