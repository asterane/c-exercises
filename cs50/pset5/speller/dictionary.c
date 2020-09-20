// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

unsigned int sz = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool miss = true;
    unsigned int ind = hash(word);
    node *ptr;

    for (ptr = table[ind]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }

        /*
        miss = false;
        for (const char *def = &(ptr->word[0]), *chk = word; *chk != '\0'; def++, chk++)
        {
            if (tolower(*chk) != *def)
            {
                miss = true;
            }
        }

        if (!miss)
        {
            return true;
        }
        */
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int val = 1;
    for (const char *ptr = word; *ptr != '\n' && *ptr != '\0'; ptr++)
    {
        val = val + (val << 5) + tolower(*ptr);
    }

    val = val & (N - 1);
    return val;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char str[LENGTH + 1];
    unsigned int ind;
    node **ptr;
    int writ;

    while (fgets(str, LENGTH + 2, file))
    {
        ind = hash(str);
        for (ptr = &(table[ind]); *ptr != NULL; ptr = &((**ptr).next));
        *ptr = malloc(sizeof(node));
        (**ptr).next = NULL;

        writ = 0;
        for (const char *chr = str; *chr != '\n'; chr++)
        {
            (**ptr).word[writ] = *chr;
            writ++;
        }
        (**ptr).word[writ] = '\0';

        sz++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sz;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *ptr, *tmp;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
        table[i] = NULL;
    }

    return true;
}
