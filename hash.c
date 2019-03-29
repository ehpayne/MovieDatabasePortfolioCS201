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

HTable *table;
Entry *newEntry(char *title, char *ID)
{
    Entry *e = malloc(sizeof(Entry));
    e->title = title;
    e->titleID = ID;
    return e;
}
HTable *newHashTable()
{
    HTable *ht = malloc(sizeof(HTable));
    ht->size = 10000000; //10 million
    
    ht->table = malloc(size * sizeof(Entry));
    
    return ht;
}

void hashTableInsert(int size)
