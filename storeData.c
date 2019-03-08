/* Author: Elizabeth Payne
 * File: readFiles.c
 * Description: This code reads in all the data files and assigns the
 * information to the corresponding variables
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readFiles.h"
#include "storeData.h"

struct BSTNode
{
    struct BSTNode *left, *right;
    char *key;
    
};

Node *newBSTNode()
{
    Node *root = malloc(sizeof(Node));
    
    root->left = NULL;
    root->right = NULL;
    root->key = NULL;
}

void storeAltTitles(TAlt *altTitles)
{

}

void storeTitleBasics(TBasic *titleBasics)
{

}

void storeTitleExecs(TExecs *execs)
{

}

void storeTitleEpisode(TEpisode *episode)
{

}

void storeTitleCrew(TCrew *crew)
{

}

void storeTitleRating(TRating *rating)
{

}

void storeNameBasics(NBasic *nameBasics)
{

}

void basicBSTInsert(int type, void *ptr)
{
    
}

