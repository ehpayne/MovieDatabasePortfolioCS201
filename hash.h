/* Author: Elizabeth Payne
 * File: hash.h
 * Description: This is the header file for hash.c which stores each record in
 *               a hash table by title.
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

//Entry is a struct for a hash table entry (contains a title (key) and a titleID)
//When the user enters a title, the hash function will return an index and the
//corresponfing title ID. The titleID will then be searched for in the BST to get
//the rest of the necessary information
typedef struct HashTableEntry Entry;

struct HashTableEntry
{
    Entry *next;
    char *title;
    char *title ID;
};

//HTable is a struct for the hash table. It contains an array of Entries and a size
typedef struct HashTable HTable;

struct HashTable
{
    int size;
    Entry **table;
}
int hashFunction(char * str, int numberOfBuckets);
void hashTableINSERT(HTable *table, char * title, char *ID);
char *hashTableSEARCH(char *title); //returns ID


