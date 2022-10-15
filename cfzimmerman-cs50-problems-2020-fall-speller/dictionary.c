// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 4050;

// Hash table
node *table[N];

int dictsize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = NULL;
    int hashcount = hash(word);
    cursor = table[hashcount];
    
    while (cursor != NULL)
    {
        if ((strcasecmp(cursor->word, word)) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // In this hash function, every letter is first made uppercase. The ASCII values of every letter of every word are added together, and the combination value is the location on the hash array. There are 4050 array places because 45 instances of the highest ASCII value, Z, yields 4050.
    int hash = 0;
    int a = 0;
    while (word[a] != 0)
    {
        a ++;
    }
    char upperword[a];
    for (int b = 0; b < a; b++)
    {
        upperword[b] = toupper(word[b]);
        hash = hash + (int)upperword[b];
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // If memory isn't successfully allocated, return false
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Allocate space for word buffer
    char *word = malloc(LENGTH + 1);
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        
        strcpy((n->word), word);

        int place = hash(word);
        
        n->next = table[place];
        table[place] = n;
        
        dictsize ++;
    }
    free(word);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Cleanup iterates over every node of every row. When cleanup moves to a new node, it leaves sacrifice behind, which frees the previous node.
    node *cleanup = NULL;
    node *sacrifice = NULL;
    int a;
    
    for (a = 0; a < 4050; a++)
    {
        cleanup = table[a];
        sacrifice = table[a];

        while (cleanup != NULL)
        {
            sacrifice = cleanup;
            cleanup = cleanup->next;
            free(sacrifice);
        }
    }
    return true;
}
