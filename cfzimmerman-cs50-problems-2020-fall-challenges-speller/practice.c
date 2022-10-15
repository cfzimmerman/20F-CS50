#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const char *word = "Hello";
    if (strcasecmp(word, "Hello") == 0)
    {
        printf("Yes!!!\n");
    }
    else if (strcasecmp(word, "Hello") != 0)
    {
        printf("Beans...\n");
    }
    else
    {
        printf("Bogus\n");
    }
}

/*
    int hashpoint = hash(word);
    node *curser = NULL;
    curser = table[hashpoint];
    while (curser != NULL)
    {
        char *twd = curser->word;
        if (strcasecmp(twd, word) == 0)
        {
            return true;
        }
        else
        {
            curser = curser->next;
        }
    }
    return false;

    */