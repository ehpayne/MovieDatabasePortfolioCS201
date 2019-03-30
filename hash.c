/* Author: Elizabeth Payne
 * File: hash.c
 * Description: This code stores each record in a hash table by title.
 *              The corresponding titleID is then sent to BST for search
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"
#include "storeData.h"
#include "hash.h"

HTable *hashTable;
Entry *newEntry(char *title, char *ID)
{
    Entry *e = malloc(sizeof(Entry));
    e->next = NULL;
    printf("Title: %s\n", title);
    printf("Title ID: %s\n", ID);
    e->title = malloc(strlen(title) * sizeof(char *));
    strcpy(e->title, title);
    e->titleID = malloc(strlen(title) * sizeof(char *));
    strcpy(e->titleID, ID);
    return e;
}
HTable *newHashTable()
{
    HTable *ht = malloc(sizeof(HTable));
    ht->size = 10000019; //10 million
    
    ht->table = malloc(ht->size * sizeof(Entry));
    
    return ht;
}

unsigned int hashFunction(char *str, int size)
{
    unsigned int index = 7717; //prime number
    for(int i = 0; i < sizeof(str); i++)
    {
        if(str[i] == '\0')
        {
            break;
        }
        index = ((73 * index) * str[i]) % size;
       // printf("index: %d\n", index);
    }
    return index;
}

unsigned int doubleHashFunction(unsigned int oldIndex, char *str, int size)
{
    unsigned int newIndex = 11831;
    
    for(int i  = 0; i < sizeof(str); i++)
    {
        if(str[i] == '\0')
        {
            break;
        }
        newIndex = (newIndex + oldIndex) * str[i] %size;
    }
    return newIndex;
}

void hashTableINSERT(int size, char *title, char *ID)
{
    printf("***********HASH TABLE INSERT************\n");
    if(size == 0)
    {
        //printf("size == 0\n");
        hashTable = newHashTable();
        //printf("table created\n");
    }
    //printf("creating entry now\n");
    Entry *entry = newEntry(title, ID);
    //printf("entry->title: %s\t entry->ID: %s\n", entry->title, entry->titleID);
    unsigned int index = hashFunction(title, hashTable->size);
    
    //printf("ORIGINAL INDEX: %u\n", index);
        
    if(hashTable->table[index] != NULL)
    {
        //printf("collision. double hash\n");
        index = doubleHashFunction(index, title, hashTable->size);
        //printf("NEW INDEX: %u\n", index);
        if(hashTable->table[index] != NULL)
        {
            //printf("slot already filled\n");
            Entry *temp = hashTable->table[index];
            Entry *back = NULL;
            while(temp != NULL)
            {
                //printf("going next\n");
                back = temp;
                temp = temp->next;
            }
            //printf("attaching new entry\n");
            back->next = entry;
        }
        else
        {
            //printf("new index empty. inserting value\n");
            hashTable->table[index] = entry;
        }
        
    }
    else
    {
        //printf("no collision. inserting value\n");
        hashTable->table[index] = entry;
    }
}
