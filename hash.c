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
    //printf("Title: %s\n", title);
    //printf("Title ID: %s\n", ID);
    e->title = strndup(title, strlen(title) + 1);
    e->titleID = strndup(ID, strlen(ID) + 1);
    return e;
}
HTable *newHashTable()
{
    HTable *ht = malloc(sizeof(HTable));
    ht->size = 10000019; //10 million
    
    ht->table = malloc(ht->size * sizeof(Entry));
    
    return ht;
}

unsigned int hashFunction(char *str)
{
    //printf("IN HASH FUNCTION\n");
    unsigned int index = 7717; //prime number
    for(int i = 0; i < sizeof(str); i++)
    {
        if(str[i] == '\0')
        {
            break;
        }
        index = ((73 * index) * str[i]) % 10000019;
        //printf("index: %d\n", index);
    }
    //printf("leaving hash function\n");
    return index;
}

unsigned int doubleHashFunction(unsigned int oldIndex, char *str)
{
    unsigned int newIndex = 11831;
    
    for(int i  = 0; i < sizeof(str); i++)
    {
        if(str[i] == '\0')
        {
            break;
        }
        newIndex = (newIndex + oldIndex) * str[i] % 10000019;
    }
    return newIndex;
}

void hashTableINSERT(int size, char *title, char *ID)
{
    //printf("here 3\n");
    //printf("***********HASH TABLE INSERT************\n");
    if(size == 0)
    {
        //printf("size == 0\n");
        hashTable = newHashTable();
        //printf("table created\n");
    }
    //printf("creating entry now\n");
    Entry *entry = newEntry(title, ID);
    //printf("entry->title: %s\t entry->ID: %s\n", entry->title, entry->titleID);
    unsigned int index = hashFunction(title);
    
    //printf("ORIGINAL INDEX: %u\n", index);
    
    if(hashTable->table[index] != NULL)
    {
        // printf("collision. double hash\n");
        index = doubleHashFunction(index, title);
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

char *hashTableSEARCH(char *title)
{
    //first possible location of the entry
    unsigned int possibleIndex1 = hashFunction(title);
    unsigned long entryLength;
    unsigned long inputLength = strlen(title);
    if(hashTable != NULL)
    {
        entryLength = strlen(hashTable->table[possibleIndex1]->title);
        //if it's there, great! Return the titleID
        if(entryLength == inputLength &&
           strcmp(hashTable->table[possibleIndex1]->title, title) == 0)
        {
            return hashTable->table[possibleIndex1]->titleID;
        }
        //it's not at the first location. Keep looking
        else
        {
            //second possible location of the entry
            unsigned int possibleIndex2 = doubleHashFunction(possibleIndex1, title);
            entryLength = strlen(hashTable->table[possibleIndex2]->title);
            //if it's there, return the titleID
            if(entryLength == inputLength &&
               strcmp(hashTable->table[possibleIndex2]->title, title) == 0)
            {
                return hashTable->table[possibleIndex2]->titleID;
            }
            //else keep going next until you find it
            else
            {
                Entry *temp = hashTable->table[possibleIndex2];
                entryLength = strlen(temp->title);
                while(temp != NULL && strcmp(temp->title, title) != 0)
                {
                    temp = temp->next;
                }
                if(temp == NULL)
                {
                    return "NOT FOUND";
                }
                else
                {
                    return temp->titleID;
                    
                }
            } //else not at the second location
            
        }//else it's not at the first location
    }// if table != NULL
    return "NOT FOUND";
}
