/*
 * Author: Elizabeth Payne
 * File: storeData.h
 * Description: This is the header file to store all the data that was read in in readFiles.c
 */

#include <stdio.h>
#include "readFiles.h"

typedef struct BSTree TreeNode;

//Constructor
TreeNode *newTree();
//Storing the data
extern void basicBSTInsert(void *node, int size);

