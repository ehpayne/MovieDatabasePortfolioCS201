/* Author: Elizabeth Payne
 * File: hash.h
 * Description: This is the header file for hash.c which stores each record in
 *               a hash table by title.
 *              The corresponding titleID is then sent to BST for search
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"


//HTable is a struct for the hash table. It contains an array of TBasic and a size
typedef struct HashTable HTable;

struct HashTable
{
    int size;
    TBasic **table;
};
extern HTable *tBasicHashTable;
//Entry *newEntry(char *title, char *ID);
HTable *newHashTable();
unsigned int hashFunction(char *str);
unsigned int doubleHashFunction(unsigned int oldIndex, char *str);
void TBasic_hashTableINSERT(int size, TBasic *tBasic);
TBasic *hashTableSEARCH(char *title); //returns ID


