// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char name[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26*26;

// Hash table
node *table[N];
char *alphabet = "abcdefghijklmnopqrstuvwxyz";

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // int i = 0;
    // int counter = 0;
    int index = hash(word);
    // node *last_node = table[bucket];
    // // printf("%s %s bucket %i\n",word,table[bucket][2].name,bucket);
    // while (last_node->next != NULL) 
    // {
    //     last_node = last_node->next;
    //     // printf("last %s\n",last_node->name);
    //     counter++;
    // }
    
    // for(int i = 0;i<counter;i++)
    // {
    //     // printf("%s\n",table[bucket][i].name);

    //     if (strcasecmp(word,(table[bucket][i]).name)==0)
    //     {   
    //         return true;
    //     }

    // }
    
    // return false;
    // return false;
    node *ptr1 = table[index];

    // Traverse linked list, looking for the word (strcasecmp)
    if (strcasecmp(ptr1->name, word) == 0)
    {
        return true ;
    }

    while (ptr1->next != NULL)
    {
        ptr1 = ptr1->next;

        if (strcasecmp(ptr1->name, word) == 0)
        {
            return true ;
        }
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 0;
    // int j = 1;
    while(alphabet[i]!=tolower(word[0]))
    {
        i++;
    }
    // while(alphabet[j-1]!=word[1])
    // {
    //     j++;
    // }
    
    return i;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE* file =fopen("dictionaries/large","r");
    
    // until the file is not at the end
    while (feof(file)==0)
    {
        
            // allocate the memory and read the word (up to 48 bits)
            char word[50];
            fscanf(file, "%s", word);
            
            int j = 0;
            int k = 0;
           
            do
            {
                if (word[0]!=alphabet[j])
                {
                    j++;
                }
                if (word[1]!=alphabet[k])
                {
                    k++;
                }
                if (word[1]=='\'')
                {
                    k = 0;
                }
            
            }while (word[0]!=alphabet[j] || (word[1]!=alphabet[k] && word[1]!='\''));
            
            
            // j = j*26;
            int bucket = j;
            // printf("word %s bucket %i\n",word,bucket);
            if (table[bucket] == NULL)
            {
                // printf("NULL\n");
                node *n = malloc(sizeof(node));
                strcpy(n->name,word); //(*n).number
                n->next = NULL;
                table[bucket] = n;
            }
            
            else
            {
                
        
                node *last_node = table[bucket];
                
                // looking for the last node in the list 
                while (last_node->next != NULL) 
                {
                    last_node = last_node->next;
                }
            
                //  allocating memory for the last node, next -> next variable 
                last_node->next = malloc(sizeof(node));
                strcpy(last_node->next->name, word);
                last_node->next->next = NULL;
                
            }

            // free(word);

    }
    printf("loaded");
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    if (table[0]== NULL)
    {
        return count; 
    }
    else
    {
    for (int i = 0; i<26; i++)
    {
        node *last_node = table[i];
        int elements = 0;
        while (last_node->next != NULL) 
        {
            last_node = last_node->next;
            elements++;
        }
        count+=elements;
    }
    return count;
    }
    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // for (int i = 0;i<26; i++)
    // {
    //     while (table!=NULL)
    //     {
    //         node *tmp = table[i]->next;
    //         free(list);
    //         list = tmp;  
    //     }
    // }
    return true;
}

