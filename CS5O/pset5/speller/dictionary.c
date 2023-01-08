// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Count of all words in dict
int elements = 0;

// Alphabet + '
char letters[27];

// Length of alphabet
#define LEN 27

// Index of a single letter in alphabet
int index_0(char letter, int start, int stop);
// Index for a word
int index_all(const char *word, int count);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 511758;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Index in a hash table
    unsigned int index = hash(word);
    // Temporary node for new element
    node *tmp = table[index];
    // Check if the word is in the dict
    while (tmp != NULL)
    {
        // Compare to a word from dict
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        // Move to another word in a list
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Assign first letter to '
    letters[0] = 39;
    // Assign all letters to the alphabet
    for (int i = 1; i < 27; i++)
    {
        letters[i] = 96 + i;
    }
    // Return index in a hash table
    return index_all(word, strlen(word));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open a dictionary
    FILE *dict = fopen(dictionary, "r");
    // Check if it's successfully opened
    if (dict == NULL)
    {
        return false;
    }
    // Array for storing one word at a time
    char single_word[LENGTH + 1];
    // Read one word at a time from the dict
    while ((fscanf(dict, "%s", single_word)) != EOF)
    {
        // Create a new node for the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy a word to a node
        strcpy(n->word, single_word);
        int index = hash(single_word);
        // Reassign pointers
        n->next = table[index];
        table[index] = n;
        // Increase a count of elements by 1
        elements++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return amount of elements
    return elements;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go through the all elements
    for (int i = 0; i < N; i++)
    {
        // Get an address of element
        node *n = table[i];
        while (n != NULL)
        {
            // Create one more pointer to "follow" previous
            node *follow = n;
            // Move tmp pointer to the next element
            n = n->next;
            // Free current element;
            free(follow);
        }
    }
    return true;
}

// Find an index of single letter in the alphabet
int index_0(char letter, int start, int end)
{
    // Check if the letter is in the middle of alphabet
    if (tolower(letter) == letters[(start + end) / 2])
    {
        return (start + end) / 2;
    }
    // Check if the letter in the left half
    else if (tolower(letter) < letters[(start + end) / 2])
    {
        // Check in the left half
        return index_0(letter, 0, (start + end) / 2);
    }
    // Check if the letter is in the right half
    else if (tolower(letter) > letters[(start + end) / 2])
    {
        // Check in the right half
        return index_0(letter, ((start + end) / 2), end);
    }
    return -1;
}

// Figure out an index of a word
int index_all(const char *word, int count)
{
    // Cuts unnecessary length
    if (count > 3)
    {
        count = 4;
    }
    // The basic case
    if (count == 1)
    {
        return (N / 26) * (index_0(word[0], 0, LEN) - 1);
    }
    // The usuall case
    return (N / 26) / pow(27, count - 1) * index_0(word[count - 1], 0, LEN) + index_all(word, count - 1);
}