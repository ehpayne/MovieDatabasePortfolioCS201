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

TAlt *tAltRoot;
TBasic *tBasicsRoot;
TExecs *tExecsRoot;



void newUser(char *username, char *password)
{
    FILE *fptr = fopen("UserInfo.txt", "a");
    fprintf(fptr, "%s %s\n", username, password);
    
    
    fclose(fptr);
}

void TAltDataBST(TAlt* altTitleNode, int size)
{
    printf("ID: %s\n", altTitleNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tAltRoot = altTitleNode;
    }
    else
    {
        TAlt *temp = tAltRoot;
        TAlt *back = NULL;
        while(temp != NULL)
        {
            back = temp;
            if(strcmp(altTitleNode->ID, temp->ID) < 0)
            {
               temp = temp->left;
                printf("going left\n");
            }
            else if(strcmp(altTitleNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                printf("going right\n");
            }
            else
            {
                //linked list for duplicates
                temp = temp->next;
                printf("going next\n");
            }
        }
        if(back == NULL)
        {
            tAltRoot = altTitleNode;
        }
        else
        {
            if(strcmp(altTitleNode->ID, back->ID) < 0)
            {
                back->left =altTitleNode;
                printf("ID: %s inserted LEFT\n", altTitleNode->ID);
            }
            else if(strcmp(altTitleNode->ID, back->ID) > 0)
            {
                back->right = altTitleNode;
                printf("ID: %s inserted RIGHT\n", altTitleNode->ID);
            }
            else
            {
                back->next = altTitleNode;
                printf("ID: %s is a duplicate\n", altTitleNode->ID);
            }
        }
    }
}

void TBasicDataBST(TBasic* titleBasicsNode, int size)
{
    printf("ID: %s\n", titleBasicsNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tBasicsRoot = titleBasicsNode;
    }
    else
    {
        TBasic *temp = tBasicsRoot;
        TBasic *back = NULL;
        while(temp != NULL)
        {
            back = temp;
            if(strcmp(titleBasicsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                printf("going left\n");
            }
            else if(strcmp(titleBasicsNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                printf("going right\n");
            }
            else
            {
                //linked list for duplicates
                temp = temp->next;
                //printf("going next\n");
            }
            
        }
        if(back == NULL)
        {
            tBasicsRoot = titleBasicsNode;
        }
        else
        {
            if(strcmp(titleBasicsNode->ID, back->ID) < 0)
            {
                back->left = titleBasicsNode;
                printf("ID: %s inserted LEFT\n", titleBasicsNode->ID);
            }
            else if(strcmp(titleBasicsNode->ID, back->ID) > 0)
            {
                back->right = titleBasicsNode;
                printf("ID: %s inserted RIGHT\n", titleBasicsNode->ID);
                
            }
            else
            {
                back->next = titleBasicsNode;
                printf("ID: %s is a duplicate\n", titleBasicsNode->ID);
            }
        }
    }
}

void TExecsDataBST(TExecs* execsNode, int size)
{
    //printf("ID: %s\n", altTitleNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tExecsRoot = execsNode;
    }
    else
    {
        TExecs *temp = tExecsRoot;
        TExecs *back = NULL;
        while(temp != NULL)
        {
            back = temp;
            if(strcmp(execsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                printf("going left\n");
            }
            else if(strcmp(execsNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                printf("going right\n");
            }
            else
            {
                //linked list for duplicates
                temp = temp->next;
                printf("going next\n");
            }
        }
        if(back == NULL)
        {
            tExecsRoot = execsNode;
        }
        else
        {
            if(strcmp(execsNode->ID, back->ID) < 0)
            {
                back->left = execsNode;
                printf("ID: %s inserted LEFT\n", execsNode->ID);
            }
            else if(strcmp(execsNode->ID, back->ID) > 0)
            {
                back->right = execsNode;
                printf("ID: %s inserted RIGHT\n", execsNode->ID);
            }
            else
            {
                back->next = execsNode;
                printf("ID: %s is a duplicate\n", execsNode->ID);
            }
        }
    }
}

void hashTable(char *ID, char *name)
{
    
}

