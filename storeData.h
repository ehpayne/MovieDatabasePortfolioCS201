/*
 * Author: Elizabeth Payne
 * File: storeData.h
 * Description: This is the header file to store all the data that was read in in readFiles.c
 */

#include <stdio.h>
#include "readFiles.h"

typedef struct HashTableElement HTElement;

//trees for storing structures
extern void TAltDataBST(TAlt* alt, int size);
extern void TBasicDataBST(TBasic* titleBasicsNode, int size);
extern void TExecsDataBST(TExecs* execsNode, int size);

//hash table/function
extern void hashTableInsert(char *ID, char* key, int size);
extern int hashFunction(char *ID, char *key);
//extern void resizeTable(HTable *table);

//storing user data
void newUser(char *username, char *password);


struct HashTableElement
{
    char *key; //title
    char *ID; //titleID
};
