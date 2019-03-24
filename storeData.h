/*
 * Author: Elizabeth Payne
 * File: storeData.h
 * Description: This is the header file to store all the data that was read in in readFiles.c
 */

#include <stdio.h>
#include "readFiles.h"

typedef struct HashTable HTable;

//trees for storing structures
extern void TAltDataBST(TAlt* alt, int size);
extern void TBasicDataBST(TBasic* titleBasicsNode, int size);
extern void TExecsDataBST(TExecs* execsNode, int size);

//hash table/function
extern HTable *newTable();
extern void hashTable(char *ID, char* key);
extern int hashFunction(char *ID, char *key);
extern void resizeTable(HTable *table);

//storing user data
void newUser(char *username, char *password);


struct HashTable
{
    int capacity;
    int size;
    char *ID;
    char *key;
};
