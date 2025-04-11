// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int word_counter = 0;

// Number of buckets in hash table (e.g., 26 for letters)
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improved: djb2-style simple hash
    unsigned long hash = 5381;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Error: Could not open dictionary file.\n");
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(dict_file, "%s", buffer) != EOF)
    {
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            fclose(dict_file);
            return false;
        }

        strcpy(new_word->word, buffer);

        int hash_value = hash(buffer);

        new_word->next = table[hash_value];
        table[hash_value] = new_word;

        word_counter++;
    }

    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
