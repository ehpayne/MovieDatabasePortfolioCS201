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
#include "menus.h"
#include "readFiles.h"
#include "hash.h"


/*Entry *newEntry(char *title, char *ID)
 {
 Entry *e = malloc(sizeof(Entry));
 e->next = NULL;
 //printf("Title: %s\n", title);
 //printf("Title ID: %s\n", ID);
 e->title = strndup(title, strlen(title) + 1);
 e->titleID = strndup(ID, strlen(ID) + 1);
 return e;
 }
 */
HTable *newHashTableTBasic()
{
    HTable *ht = malloc(sizeof(HTable));
    ht->size = 18000000; //18 million
    
    ht->table = malloc(ht->size * sizeof(TBasic));
    
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
        index = ((73 * index) * str[i]) % 18000000;
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
        newIndex = ((newIndex * oldIndex) * str[i]) % 18000000;
    }
    return newIndex;
}

void TBasic_hashTableINSERT(int size, TBasic *entry)
{
    //printf("here 3\n");
    //printf("***********HASH TABLE INSERT************\n");
    if(size == 0)
    {
        //printf("size == 0\n");
        tBasicHashTable = newHashTableTBasic();
        //printf("table created\n");
    }
    //printf("creating entry now\n");
    
    //printf("entry->title: %s\t entry->ID: %s\n", entry->title, entry->titleID);
    unsigned int index = hashFunction(entry->primaryTitle);
    
    //printf("ORIGINAL INDEX: %u\n", index);
    
    if(tBasicHashTable->table[index] != NULL)
    {
        // printf("collision. double hash\n");
        index = doubleHashFunction(index, entry->primaryTitle);
        //printf("NEW INDEX: %u\n", index);
        if(tBasicHashTable->table[index] != NULL)
        {
            //printf("slot already filled\n");
            TBasic *temp = tBasicHashTable->table[index];
            TBasic *back = NULL;
            while(temp != NULL)
            {
                //printf("going next\n");
                back = temp;
                temp = temp->next;
            }
            //printf("attaching new entry\n");
            back->next = entry;
            //printf("%s:%s = %d\t Actual Primary: %luTable Primary:%lu:\n",
            //       entry->ID,entry->primaryTitle, index, strlen(entry->primaryTitle),
            //       strlen(back->next->primaryTitle));
        }
        else
        {
            //printf("new index empty. inserting value\n");
            tBasicHashTable->table[index] = entry;
            //printf("%s:%s = %d\t Actual Primary: %luTable Primary:%lu:\n",
            //      entry->ID,entry->primaryTitle, index, strlen(entry->primaryTitle),
            //      strlen(tBasicHashTable->table[index]->primaryTitle));
            
        }
        
    }
    else
    {
        //printf("no collision. inserting value\n");
        tBasicHashTable->table[index] = entry;
        //printf("%s:%s = %d\t Actual Primary: %luTable Primary:%lu:\n",
        //      entry->ID,entry->primaryTitle, index, strlen(entry->primaryTitle),
        //      strlen(tBasicHashTable->table[index]->primaryTitle));
    }
    
}

TBasic *hashTableSEARCH(char *title)
{
    //first possible location of the entry
    unsigned int possibleIndex1 = hashFunction(title);
    unsigned long entryLength = 0;
    unsigned long inputLength = strlen(title);
    if(tBasicHashTable != NULL)
    {
        entryLength = strlen(tBasicHashTable->table[possibleIndex1]->primaryTitle);
        //if it's there, great! Return the titleID
        if(entryLength == inputLength &&
           strcmp(tBasicHashTable->table[possibleIndex1]->primaryTitle, title) == 0)
        {
            return tBasicHashTable->table[possibleIndex1];
        }
        else if(tBasicHashTable->table[possibleIndex1] == NULL)
        {
            return NULL;
        }
        //it's not at the first location. Keep looking
        else
        {
            //second possible location of the entry
            unsigned int possibleIndex2 = doubleHashFunction(possibleIndex1, title);
            entryLength = strlen(tBasicHashTable->table[possibleIndex2]->primaryTitle);
            //if it's there, return the titleID
            if(entryLength == inputLength &&
               strcmp(tBasicHashTable->table[possibleIndex2]->primaryTitle, title) == 0)
            {
                return tBasicHashTable->table[possibleIndex2];
            }
            else if(tBasicHashTable->table[possibleIndex2] == NULL)
            {
                return NULL;
            }
            //else keep going next until you find it
            else
            {
                TBasic *temp = tBasicHashTable->table[possibleIndex2];
                entryLength = strlen(temp->primaryTitle);
                while(temp != NULL && strcmp(temp->primaryTitle, title) != 0)
                {
                    temp = temp->next;
                }
                if(temp == NULL)
                {
                    return NULL;
                }
                else
                {
                    return temp;
                    
                }
            } //else not at the second location
            
        }//else it's not at the first location
    }// if table != NULL
    else
    {
        return NULL;
    }
    
}
